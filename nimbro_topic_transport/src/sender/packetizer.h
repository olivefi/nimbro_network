// Fragment a message into (UDP) packets
// Author: Max Schwarz <max.schwarz@uni-bonn.de>

#ifndef TT_PACKETIZER_H
#define TT_PACKETIZER_H

#include <vector>
#include <mutex>

#include "topic.h"
#include "message.h"

namespace nimbro_topic_transport
{

class TopicPacketizer;

struct Packet
{
	std::vector<uint8_t> data;
	std::size_t length;
};

class Packetizer
{
public:
	typedef std::shared_ptr<Packetizer> Ptr;
	typedef std::shared_ptr<const Packetizer> ConstPtr;

private:
	friend class TopicPacketizer;

	uint32_t allocateMessageID();

	std::mutex m_mutex;
	uint32_t m_messageID = 0;
};

class TopicPacketizer
{
public:
	TopicPacketizer(const Packetizer::Ptr& packetizer, const Topic::ConstPtr& topic);
	~TopicPacketizer();

	std::vector<Packet> packetize(const Message::ConstPtr& msg);
private:
	Packetizer::Ptr m_packetizer;
	float m_fec = 0.0;
};

}

#endif
