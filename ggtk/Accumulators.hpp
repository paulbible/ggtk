/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef ACCUMULATORS
#define ACCUMULATORS

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/covariance.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/variates/covariate.hpp>

//! The Accumulators namespace provides min, max, and average accumulators to the broader code base.
/*!
	This namespace defines accumulator types from boost. Also provided are specific extactors
	that will return the accumulator's current value.
*/
namespace Accumulators{

	//to be able to call Accumulators::covariate1 instread of boost::accumulators::covariate1
	using namespace boost::accumulators;

	//typedefs
	/*! MinAccumulator
	\brief A helper type wrapping boost accumulators.
	*/
	typedef boost::accumulators::accumulator_set< double,
		boost::accumulators::stats< boost::accumulators::tag::min >  > MinAccumulator;

	/*! MaxAccumulator
	\brief A helper type wrapping boost accumulators.
	*/
	typedef boost::accumulators::accumulator_set< double,
		boost::accumulators::stats< boost::accumulators::tag::max >  > MaxAccumulator;

	/*! MeanAccumulator
	\brief A helper type wrapping boost accumulators.
	*/
	typedef boost::accumulators::accumulator_set< double,
		boost::accumulators::stats<	boost::accumulators::tag::mean > > MeanAccumulator;

	/*! MeanAccumulator
	\brief A helper type wrapping boost accumulators.
	*/
	typedef boost::accumulators::accumulator_set< double,
		boost::accumulators::stats<	boost::accumulators::tag::mean > > MeanAccumulator;

	/*! SimpleAccumulator
	\brief A helper type wrapping min, max, and mean accumulators.
	*/
	typedef boost::accumulators::accumulator_set< double,
		boost::accumulators::stats<
			boost::accumulators::tag::max,
			boost::accumulators::tag::min,
			boost::accumulators::tag::mean > > SimpleAccumulator;


	/*! CovarianceAccumulator
	\brief A helper type wrapping the covariance accumulator.
	*/
	typedef boost::accumulators::accumulator_set< double,
		boost::accumulators::stats< 
		    boost::accumulators::tag::covariance<double,
			  boost::accumulators::tag::covariate1> > > CovarianceAccumulator;

	/*! VarianceAccumulator
	\brief A helper type wrapping the variance accumulator.
	*/
	typedef boost::accumulators::accumulator_set< double,
		boost::accumulators::stats< 
		    boost::accumulators::tag::variance> > VarianceAccumulator;

	//extractors
	/*! extractMin
	\brief A helper helper function to extract the min.
	*/
	inline double extractMin(const MinAccumulator &acc){
		return  boost::accumulators::min(acc);
	}

	/*! extractMax
	\brief A helper helper function to extract the max.
	*/
	inline double extractMax(const MaxAccumulator &acc){
		return  boost::accumulators::max(acc);
	}

	/*! extractMean
	\brief A helper helper function to extract the mean.
	*/
	inline double extractMean(const MeanAccumulator &acc){
		return  boost::accumulators::mean(acc);
	}

	/*! extractMin
	\brief An overlaoded helper helper function to extract the min.
	*/
	inline double extractMin(const SimpleAccumulator &acc){
		return  boost::accumulators::min(acc);
	}

	/*! extractMax
	\brief An overlaoded helper helper function to extract the max.
	*/
	inline double extractMax(const SimpleAccumulator &acc){
		return  boost::accumulators::max(acc);
	}

	/*! extractMean
	\brief An overlaoded helper helper function to extract the mean.
	*/
	inline double extractMean(const SimpleAccumulator &acc){
		return  boost::accumulators::mean(acc);
	}

	/*! extractCovariance
	\brief A helper helper function to extract the covariance.
	*/
	inline double extractCovariance(const CovarianceAccumulator &acc){
		return  boost::accumulators::covariance(acc);
	}

	/*! extractVariance
	\brief A helper helper function to extract the variance.
	*/
	inline double extractVariance(const VarianceAccumulator &acc){
		return  boost::accumulators::variance(acc);
	}

	/*! extractVariance
	\brief A helper helper function to extract the variance.
	*/
	inline double extractSD(const VarianceAccumulator &acc){
		return  sqrt(boost::accumulators::variance(acc));
	}

};
#endif
