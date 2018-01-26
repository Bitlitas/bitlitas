/// @file
/// @author rfree (current maintainer in bitlitas.cc project)
/// @brief interface for throttling of connection (count and rate-limit speed etc)

// Copyright (c) 2018, Bitlitas
// All rights reserved.

/* rfree: throttle basic interface */
/* rfree: also includes the manager for singeton/global such objects */


#ifndef INCLUDED_network_throttle_hpp
#define INCLUDED_network_throttle_hpp

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <atomic>

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/thread/thread.hpp>

#include "syncobj.h"

#include "net/net_utils_base.h" 
#include "misc_log_ex.h" 
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/chrono.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 
#include "misc_language.h"
#include "pragma_comp_defs.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

#include <memory>
#include <mutex>
#include <fstream>

namespace epee
{
namespace net_utils
{

// just typedefs to in code define the units used. TODO later it will be enforced that casts to other numericals are only explicit to avoid mistakes? use boost::chrono?
typedef double network_speed_kbps;   // externally, for parameters and return values, all defined in kilobytes per second
typedef double network_speed_bps;    // throttle-internally, bytes per second
typedef double network_time_seconds;
typedef double network_MB;

class i_network_throttle;

/***
@brief All information about given throttle - speed calculations
*/
struct calculate_times_struct {
		double average;
		double window;
		double delay;
		double recomendetDataSize;
};
typedef calculate_times_struct calculate_times_struct;


/*** 
@brief Access to simple throttles, with singlton to access global network limits
*/
class network_throttle_manager {
	// provides global (singleton) in/inreq/out throttle access

	// [[note1]] see also http://www.nuonsoft.com/blog/2012/10/21/implementing-a-thread-safe-singleton-with-c11/
	// [[note2]] _inreq is the requested in traffic - we anticipate we will get in-bound traffic soon as result of what we do (e.g. that we sent network downloads requests)
	
	//protected:
	public: // XXX

    static boost::mutex m_lock_get_global_throttle_in;
    static boost::mutex m_lock_get_global_throttle_inreq;
    static boost::mutex m_lock_get_global_throttle_out;

		friend class connection_basic; // FRIEND - to directly access global throttle-s. !! REMEMBER TO USE LOCKS!
		friend class connection_basic_pimpl; // ditto

	public:
		static i_network_throttle & get_global_throttle_in(); ///< singleton ; for friend class ; caller MUST use proper locks! like m_lock_get_global_throttle_in
		static i_network_throttle & get_global_throttle_inreq(); ///< ditto ; use lock ... use m_lock_get_global_throttle_inreq obviously
		static i_network_throttle & get_global_throttle_out(); ///< ditto ; use lock ... use m_lock_get_global_throttle_out obviously
};



/***
@brief interface for the throttle, see the derivated class
*/
class i_network_throttle {
	public:
		virtual void set_name(const std::string &name)=0;
		virtual void set_target_speed( network_speed_kbps target )=0;
		virtual network_speed_kbps get_target_speed()=0;

		virtual void handle_trafic_exact(size_t packet_size) =0; // count the new traffic/packet; the size is exact considering all network costs
		virtual void handle_trafic_tcp(size_t packet_size) =0; // count the new traffic/packet; the size is as TCP, we will consider MTU etc
		virtual void tick() =0; // poke and update timers/history
		
		// time calculations:
		
		virtual void calculate_times(size_t packet_size, calculate_times_struct &cts, bool dbg, double force_window) const =0; // assuming sending new package (or 0), calculate:
		// Average, Window, Delay, Recommended data size ; also gets dbg=debug flag, and forced widnow size if >0 or -1 for not forcing window size 

		// Average speed, Window size, recommended Delay to sleep now, Recommended size of data to send now

		virtual network_time_seconds get_sleep_time(size_t packet_size) const =0; // gets the D (recommended Delay time) from calc
		virtual network_time_seconds get_sleep_time_after_tick(size_t packet_size) =0; // ditto, but first tick the timer

		virtual size_t get_recommended_size_of_planned_transport() const =0; // what should be the recommended limit of data size that we can transport over current network_throttle in near future

		virtual double get_time_seconds() const =0; // a timer
        virtual void logger_handle_net(const std::string &filename, double time, size_t size)=0;


};


// ... more in the -advanced.h file


} // namespace net_utils
} // namespace epee


#endif



