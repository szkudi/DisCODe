/*
 * headers.h
 *
 *  Created on: Nov 5, 2010
 *      Author: mboryn
 */

#ifndef DISCODE_SENSOR_HEADERS_H_
#define DISCODE_SENSOR_HEADERS_H_

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace Proxies {

namespace Mrrocpp {

struct initiate_message_header
{
	int data_size;
	bool is_rpc_call;

	template <class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & data_size;
		ar & is_rpc_call;
	}
};

struct reading_message_header
{
	int data_size;
	bool is_rpc_call;

	template <class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & data_size;
		ar & is_rpc_call;
	}
};

} // namespace Mrrocpp {

} // namespace Proxies

#endif /* DISCODE_SENSOR_HEADERS_H_ */
