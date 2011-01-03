/*
 * Reading.hpp
 *
 */

#ifndef READING_HPP_
#define READING_HPP_

#include "xdr/xdr_oarchive.hpp"
#include <boost/shared_ptr.hpp>
#include "Logger.hpp"

namespace Proxies {

namespace Mrrocpp {

class Reading
{
public:
	Reading()
	{
	}

	virtual ~Reading()
	{
	}

	virtual Reading* clone() = 0;

	virtual void printInfo()
	{
		LOG(LNOTICE) << "Reading::printInfo()\n";
	}

	virtual void send(boost::shared_ptr<xdr_oarchive<> > & ar) = 0;
private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		LOG(LNOTICE) << "Reading::serialize()\n";
	}

};

}//namespace Mrrocpp
}//namespace Proxies

#endif /* READING_HPP_ */
