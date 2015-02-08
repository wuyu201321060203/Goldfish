#include <DM/RASTunnel.h>
#include <DM/Initializer.h>

using namespace muduo;
using namespace muduo::net;

#define RAS_CONNECTED 1
#define RAS_DISCONNECTED 0

RASTunnel::RASTunnel(muduo::net::EventLoop* loop , muduo::net::InetAddress const& addr):
                    ResourceManager(loop , addr) , _status(RAS_DISCONNECTED),
                    _rasCodec(boost::bind(&ProtobufDispatcher::onProtobufMessage,
                                &Initializer::getDispatcher() , _1 , _2 , _3)),
                    _waiting4NcReply(false)
{
    ( Initializer::getDispatcher() ).registerMessageCallback(
        FwmRcProto::FWMRCRegister::descriptor(),
        boost::bind(&RASTunnel::onRegisterCallback , this , _1 , _2 , _3));

    ( Initializer::getDispatcher() ).registerMessageCallback(
        FwmRcProto::RespondRequestSlaveResource::descriptor(),
        boost::bind(&RASTunnel::onApplyResourceReplyFromRC , this , _1 , _2 , _3));
}

void RASTunnel::init()
{
    _rasMasterClient.connect();
}

void RASTunnel::applyResource(MessagePtr const& msg,
                              muduo::net::TcpConnectionPtr const& cliConn)
{
    _cliConnVec.push_back(cliConn);
    DomainCreateMsgPtr query = muduo::down_pointer_cast<DomainCreateMsg>(msg);
    RequestSlaveResource apply;
    (apply.mutable_framework_instance_info())->set_framework_id(
                                                Initializer::getFrameworkID());

    (apply.mutable_framework_instance_info())->set_framework_instance_id(
                                        Initializer::getFrameworkInstanceID());

    apply.set_module_name("DC");
    ::FwmRcProto::EachMachineResourceInfo* eachResourceInfo =
                                                apply.add_each_resource_info();
    eachResourceInfo->set_ip("*");
    (eachResourceInfo->mutable_resource_info())->set_cpu_num(query->corenum());
    (eachResourceInfo->mutable_resource_info())->set_cpu_mem_size(query->memsize());
    (Initializer::getCodec()).send(_rasMasterClient.connection() , apply);
}

void RASTunnel::revokeResource(MessagePtr const& msg,
                               muduo::net::TcpConnectionPtr const& cliConn)
{

}

void RASTunnel::onApplyResourceReplyFromRC(muduo::net::TcpConnectionPtr const& conn,
                                           MessagePtr const& msg,
                                           muduo::Timestamp receiveTime)
{
    boost::shared_ptr<RespondRequestSlaveResource> reply =
        muduo::down_pointer_cast<RespondRequestSlaveResource>(msg);

    if(1 != reply->address_resource_info_size())//RAS must make sure find a suitable NC for my demand
    {
        LOG_INFO << "RAS has not enough resource for " << conn->name() << "'s demand";
        return;
    }
    ::FwmRcProto::EachNCResourceAddress& ncAddr = reply->address_resource_info(0);
    ::FwmRcProto::NetAddress const& netAddr = ncAddr.nc_net_address();
    STDSTR ncIP = netAddr.ip();
    uint32_t ncPort = netAddr.port();
    InetAddress ncAddress(ncIP , ncPort);
    ::FwmRcProto::ResourceInfo& resuorceInfo = ncAddr->resource_info();
    double cpu_num = resourceInfo.cpu_num();
    uint32_t cpu_mem_size = resourceInfo.cpu_mem_size();
    /*
    if(_waiting4NcReply)
    {

    }
    _waiting4NcReply = true;
    */
    TcpClientPtr rasSlaveClient(new TcpClient(&Initializer::getEventLoop(),
                                        ncAddress,
                                        ""));

    rasSlaveClient->setConnectionCallback(boost::bind(&RASTunnel::onConnectionCallbackFromNC,
                                                this , _1 , cpu_num , cpu_mem_size));

    rasSlaveClient->setMessageCallback(boost::bind(&ProtobufRASCodec::onMessage,
                                        &_rasCodec , _1 , _2 , _3);

    _rasSlaveClientVec.push_back(rasSlaveClient);
    rasSlaveClient->connect();
}

void RASTunnel::onApplyResourceReplyFromNC(muduo::net::TcpConnectionPtr const&,
                                           MessagePtr const&,
                                           muduo::Timestamp)
{

}

void RASTunnel::onRevokeResourceReply(muduo::net::TcpConnectionPtr const&,
                                      MessagePtr const&,
                                      muduo::Timestamp)
{

}

void RASTunnel::onConnectionCallbackFromRC(TcpConnectionPtr const& conn)
{
    if(conn->connected())
    {
        _status = RAS_CONNECTED;
        //heartbeat
        register2RAS(conn);
    }
    else
    {
        LOG_INFO << "disconnect to RC of RAS";
        _status = RAS_DISCONNECTED;
    }
}

void RASTunnel::onConnectionCallbackFromNC(TcpConnectionPtr const& conn , double cpu_num,
                                           uint32_t cpu_mem_size)
{
    if(conn->connected())
    {
        ::FwmNcProto::StartSlave reply;
        ::FwmNcProto::FrameworkInstanceInfo* frameworkInstanceInfo =
            reply.mutable_framework_instance_info();
        frameworkInstanceInfo->set_framework_id(Initializer::getFrameworkID());
        frameworkInstanceInfo->set_framework_instance_id(
                                        Initializer::getFrameworkInstanceID());

        ::FwmNcProto::DockerImageInfo* imageInfo = reply.mutable_docker_image_info();
        imageInfo->set_tag(Initializer::getDockerTag());
        imageInfo->set_locate_file(Initializer::getExecFilePathList());
        imageInfo->set_module_name("DC");

        ::FwmNcProto::ResourceInfo* resourceInfo = reply.mutable_resource_infO();
        resourceInfo->set_cpu_num(cpu_num);
        resourceInfo->set_cpu_mem_size(cpu_mem_size);

        reply.set_listen_port_num(xx);//TODO
        ::FwmNcProto::NetAddress* dmNetAddr = reply.mutable_fm_master_net_address();
        dmNetAddr->set_ip(Initializer::getDMIP());
        dmNetAddr->set_port(Initializer::getDMPort());

        (Initializer::getCodec()).send(conn , reply);
    }
    else
    {
        LOG_INFO << "disconnect to NC of RAS";
    }
}

void RASTunnel::register2RAS(TcpConnectionPtr const& conn)
{
    FwmRcProto::FWMRCRegister msg;
    (msg.mutable_framework_instance_info())->set_framework_id(
                                                Initializer::getFrameworkID());

    (msg.mutable_framework_instance_info())->set_framework_instance_id(
                                        Initializer::getFrameworkInstanceID());

    (msg.mutable_framework_master_info())->set_module_name(MODULE_NAME);
    (msg.mutable_framework_master_info())->set_fw_master_ip(Initializer::getDMIP());
    ( Initializer::getCodec() ).send(conn , msg);
}

void RASTunnel::onRegisterCallback(TcpConnectionPtr const& conn,
                                   MessagePtr const& msg,
                                   muduo::Timestamp receiveTime)
{
    boost::shared_ptr<FWMRCRegisterACK> reply =
        muduo::down_pointer_cast<FWMRCRegisterACK>(msg);
    if(SUCCESS != reply->statuscode())
    {
        _statuc = RAS_DISCONNECTED;
        LOG_INFO << "failed to register to RAS";
    }
}