/**
@file
@author rfree (current maintainer in bitlitas.cc project)
@brief interface for throttling of connection (count and rate-limit speed etc) 
@details <PRE>

Throttling work by:
1) taking note of all traffic (hooks added e.g. to connection class) and measuring speed
2) depending on that information we sleep before sending out data (or send smaller portions of data)
3) depending on the information we can also sleep before sending requests or ask for smaller sets of data to download

</PRE> 

@image html images/net/rate1-down-1k.png
@image html images/net/rate1-down-full.png
@image html images/net/rate1-up-10k.png
@image html images/net/rate1-up-full.png
@image html images/net/rate2-down-100k.png
@image html images/net/rate2-down-10k.png
@image html images/net/rate2-down-50k.png
@image html images/net/rate2-down-full.png
@image html images/net/rate2-up-100k.png
@image html images/net/rate2-up-10k.png
@image html images/net/rate3-up-10k.png


*/

// Copyright (c) 2018, Bitlitas
// All rights reserved.

#include "net/network_throttle-detail.hpp"

namespace epee
{
namespace net_utils
{

// ================================================================================================
// network_throttle_manager
// ================================================================================================

// ================================================================================================
// static:
boost::mutex network_throttle_manager::m_lock_get_global_throttle_in;
boost::mutex network_throttle_manager::m_lock_get_global_throttle_inreq;
boost::mutex network_throttle_manager::m_lock_get_global_throttle_out;

// ================================================================================================
// methods:
i_network_throttle & network_throttle_manager::get_global_throttle_in() { 
	static network_throttle obj_get_global_throttle_in("in/all","<<< global-IN",10);
	return obj_get_global_throttle_in;
}



i_network_throttle & network_throttle_manager::get_global_throttle_inreq() { 
	static network_throttle obj_get_global_throttle_inreq("inreq/all", "<== global-IN-REQ",10);
	return obj_get_global_throttle_inreq;
}


i_network_throttle & network_throttle_manager::get_global_throttle_out() { 
	static network_throttle obj_get_global_throttle_out("out/all", ">>> global-OUT",10);
	return obj_get_global_throttle_out;
}




network_throttle_bw::network_throttle_bw(const std::string &name1) 
	: m_in("in/"+name1, name1+"-DOWNLOAD"), m_inreq("inreq/"+name1, name1+"-DOWNLOAD-REQUESTS"), m_out("out/"+name1, name1+"-UPLOAD")
{ }




} // namespace 
} // namespace 





