/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*!
 Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl
 Copyright (C) 2003, 2004, 2005, 2006, 2007 StatPro Italia srl
 Copyright (C) 2004 Ferdinando Ametrano
 Copyright (C) 2016 Paolo Mazzocchi
 Copyright (C) 2016 Stefano Fondi

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*  This example shows how to set up a Term Structure and then price a simple
    swap.
*/

// the only header you need to use QuantLib
#include <ql/quantlib.hpp>

#ifdef BOOST_MSVC
/* Uncomment the following lines to unmask floating-point
   exceptions. Warning: unpredictable results can arise...

   See http://www.wilmott.com/messageview.cfm?catid=10&threadid=9481
   Is there anyone with a definitive word about this?
*/
// #include <float.h>
// namespace { unsigned int u = _controlfp(_EM_INEXACT, _MCW_EM); }
#endif

#include <boost/timer.hpp>
#include <iostream>
#include <iomanip>

using namespace QuantLib;

#ifdef BOOST_MSVC
#  ifdef QL_ENABLE_THREAD_SAFE_OBSERVER_PATTERN
#    include <ql/auto_link.hpp>
#    define BOOST_LIB_NAME boost_system
#    include <boost/config/auto_link.hpp>
#    undef BOOST_LIB_NAME
#    define BOOST_LIB_NAME boost_thread
#    include <boost/config/auto_link.hpp>
#    undef BOOST_LIB_NAME
#  endif
#endif

#if defined(QL_ENABLE_SESSIONS)
namespace QuantLib {

    Integer sessionId() { return 0; }

}
#endif


int main(int, char* []) {

    try {

        boost::timer timer;
        std::cout << std::endl;

        /*********************
        ***  MARKET DATA  ***
        *********************/

        Calendar calendar = UnitedKingdom(UnitedKingdom::Exchange);
        Date settlementDate(05, October, 2016);
        // must be a business day
        settlementDate = calendar.adjust(settlementDate);

        Integer fixingDays = 0;
        Date todaysDate = calendar.advance(settlementDate, -fixingDays, Days);
        // nothing to do with Date::todaysDate
        Settings::instance().evaluationDate() = todaysDate;


        todaysDate = Settings::instance().evaluationDate();
        std::cout << "Today: " << todaysDate.weekday()
                    << ", " << todaysDate << std::endl;

        std::cout << "Settlement date: " << settlementDate.weekday()
                    << ", " << settlementDate << std::endl;

        // ON Instruments
        // deposits
        Rate donQuote = 0.002281;
        //OIS
        Rate oisSwQuote = 0.00214;
        Rate ois2wQuote = 0.00214;
        Rate ois1mQuote = 0.0021;
        Rate ois2mQuote = 0.00199;
        Rate ois3mQuote = 0.00187;
        Rate ois4mQuote = 0.00183;
        Rate ois5mQuote = 0.00175;
        Rate ois6mQuote = 0.00168;
        Rate ois7mQuote = 0.00163;
        Rate ois8mQuote = 0.00158;
        Rate ois9mQuote = 0.00154;
        Rate ois10mQuote = 0.00149;
        Rate ois11mQuote = 0.00146;
        Rate ois1yQuote = 0.00142;
        Rate ois2yQuote = 0.00123;
        Rate ois3yQuote = 0.00135;
        Rate ois4yQuote = 0.00171;
        Rate ois5yQuote = 0.00218;
        Rate ois6yQuote = 0.00268;
        Rate ois7yQuote = 0.0033;
        Rate ois8yQuote = 0.00397;
        Rate ois9yQuote = 0.00467;
        Rate ois10yQuote = 0.00533;
        Rate ois12yQuote = 0.00644;
        Rate ois15yQuote = 0.00758;
        Rate ois20yQuote = 0.00846;
        Rate ois25yQuote = 0.00869;
        Rate ois30yQuote = 0.00875;
        Rate ois40yQuote = 0.00835;
        Rate ois50yQuote = 0.0081;
        Rate ois60yQuote = 0.00812;

        // 3 Months Libor Instruments
        // synth deposits
        Rate d1mQuote = 0.004194;
        Rate d2mQuote = 0.004016;
        Rate d3mQuote = 0.003849;
        // futures
        Real fut1Quote = 99.6525;
        Real fut2Quote = 99.685;
        Real fut3Quote = 99.705;
        Real fut4Quote = 99.715;
        Real fut5Quote = 99.72;
        Real fut6Quote = 99.715;
        Real fut7Quote = 99.705;
        Real fut8Quote = 99.695;
        // swaps
        Rate s3yQuote = 0.00322;
        Rate s4yQuote = 0.0036;
        Rate s5yQuote = 0.00411;
        Rate s6yQuote = 0.00467;
        Rate s7yQuote = 0.00529;
        Rate s8yQuote = 0.00595;
        Rate s9yQuote = 0.00662;
        Rate s10yQuote = 0.00726;
        Rate s12yQuote = 0.00831;
        Rate s15yQuote = 0.00936;
        Rate s20yQuote = 0.01014;
        Rate s25yQuote = 0.01029;
        Rate s30yQuote = 0.01028;
        Rate s40yQuote = 0.00978;
        Rate s50yQuote = 0.00946;
        Rate s60yQuote = 0.00942;


        /********************
        ***    QUOTES    ***
        ********************/

        // SimpleQuote stores a value which can be manually changed;
        // other Quote subclasses could read the value from a database
        // or some kind of data feed.

        // ON Instruments
        // deposits
        boost::shared_ptr<Quote> donRate(new SimpleQuote(donQuote));
        //OIS
        boost::shared_ptr<Quote> oisSwRate(new SimpleQuote(oisSwQuote));
        boost::shared_ptr<Quote> ois2wRate(new SimpleQuote(ois2wQuote));
        boost::shared_ptr<Quote> ois1mRate(new SimpleQuote(ois1mQuote));
        boost::shared_ptr<Quote> ois2mRate(new SimpleQuote(ois2mQuote));
        boost::shared_ptr<Quote> ois3mRate(new SimpleQuote(ois3mQuote));
        boost::shared_ptr<Quote> ois4mRate(new SimpleQuote(ois4mQuote));
        boost::shared_ptr<Quote> ois5mRate(new SimpleQuote(ois5mQuote));
        boost::shared_ptr<Quote> ois6mRate(new SimpleQuote(ois6mQuote));
        boost::shared_ptr<Quote> ois7mRate(new SimpleQuote(ois7mQuote));
        boost::shared_ptr<Quote> ois8mRate(new SimpleQuote(ois8mQuote));
        boost::shared_ptr<Quote> ois9mRate(new SimpleQuote(ois9mQuote));
        boost::shared_ptr<Quote> ois10mRate(new SimpleQuote(ois10mQuote));
        boost::shared_ptr<Quote> ois11mRate(new SimpleQuote(ois11mQuote));
        boost::shared_ptr<Quote> ois1yRate(new SimpleQuote(ois1yQuote));
        boost::shared_ptr<Quote> ois2yRate(new SimpleQuote(ois2yQuote));
        boost::shared_ptr<Quote> ois3yRate(new SimpleQuote(ois3yQuote));
        boost::shared_ptr<Quote> ois4yRate(new SimpleQuote(ois4yQuote));
        boost::shared_ptr<Quote> ois5yRate(new SimpleQuote(ois5yQuote));
        boost::shared_ptr<Quote> ois6yRate(new SimpleQuote(ois6yQuote));
        boost::shared_ptr<Quote> ois7yRate(new SimpleQuote(ois7yQuote));
        boost::shared_ptr<Quote> ois8yRate(new SimpleQuote(ois8yQuote));
        boost::shared_ptr<Quote> ois9yRate(new SimpleQuote(ois9yQuote));
        boost::shared_ptr<Quote> ois10yRate(new SimpleQuote(ois10yQuote));
        boost::shared_ptr<Quote> ois12yRate(new SimpleQuote(ois12yQuote));
        boost::shared_ptr<Quote> ois15yRate(new SimpleQuote(ois15yQuote));
        boost::shared_ptr<Quote> ois20yRate(new SimpleQuote(ois20yQuote));
        boost::shared_ptr<Quote> ois25yRate(new SimpleQuote(ois25yQuote));
        boost::shared_ptr<Quote> ois30yRate(new SimpleQuote(ois30yQuote));
        boost::shared_ptr<Quote> ois40yRate(new SimpleQuote(ois40yQuote));
        boost::shared_ptr<Quote> ois50yRate(new SimpleQuote(ois50yQuote));
        boost::shared_ptr<Quote> ois60yRate(new SimpleQuote(ois60yQuote));

        // 3 Months Libor Instruments
        // synth deposits
        boost::shared_ptr<Quote> d1mRate(new SimpleQuote(d1mQuote));
        boost::shared_ptr<Quote> d2mRate(new SimpleQuote(d2mQuote));
        boost::shared_ptr<Quote> d3mRate(new SimpleQuote(d3mQuote));
        // futures
        boost::shared_ptr<Quote> fut1Price(new SimpleQuote(fut1Quote));
        boost::shared_ptr<Quote> fut2Price(new SimpleQuote(fut2Quote));
        boost::shared_ptr<Quote> fut3Price(new SimpleQuote(fut3Quote));
        boost::shared_ptr<Quote> fut4Price(new SimpleQuote(fut4Quote));
        boost::shared_ptr<Quote> fut5Price(new SimpleQuote(fut5Quote));
        boost::shared_ptr<Quote> fut6Price(new SimpleQuote(fut6Quote));
        boost::shared_ptr<Quote> fut7Price(new SimpleQuote(fut7Quote));
        boost::shared_ptr<Quote> fut8Price(new SimpleQuote(fut8Quote));
        // swaps
        boost::shared_ptr<Quote> s3yRate(new SimpleQuote(s3yQuote));
        boost::shared_ptr<Quote> s4yRate(new SimpleQuote(s4yQuote));
        boost::shared_ptr<Quote> s5yRate(new SimpleQuote(s5yQuote));
        boost::shared_ptr<Quote> s6yRate(new SimpleQuote(s6yQuote));
        boost::shared_ptr<Quote> s7yRate(new SimpleQuote(s7yQuote));
        boost::shared_ptr<Quote> s8yRate(new SimpleQuote(s8yQuote));
        boost::shared_ptr<Quote> s9yRate(new SimpleQuote(s9yQuote));
        boost::shared_ptr<Quote> s10yRate(new SimpleQuote(s10yQuote));
        boost::shared_ptr<Quote> s12yRate(new SimpleQuote(s12yQuote));
        boost::shared_ptr<Quote> s15yRate(new SimpleQuote(s15yQuote));
        boost::shared_ptr<Quote> s20yRate(new SimpleQuote(s20yQuote));
        boost::shared_ptr<Quote> s25yRate(new SimpleQuote(s25yQuote));
        boost::shared_ptr<Quote> s30yRate(new SimpleQuote(s30yQuote));
        boost::shared_ptr<Quote> s40yRate(new SimpleQuote(s40yQuote));
        boost::shared_ptr<Quote> s50yRate(new SimpleQuote(s50yQuote));
        boost::shared_ptr<Quote> s60yRate(new SimpleQuote(s60yQuote));


        /************************
        *** OIS RATE HELPERS ***
        ************************/

        // RateHelpers are built from the above quotes together with
        // other instrument dependant infos.  Quotes are passed in
        // relinkable handles which could be relinked to some other
        // data source later.

        // ois

        boost::shared_ptr<OvernightIndex> overnightLegIndex(new Sonia());

        boost::shared_ptr<RateHelper> oSw(new OISRateHelper(
            0, 1 * Weeks, Handle<Quote>(oisSwRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o2w(new OISRateHelper(
            0, 2 * Weeks, Handle<Quote>(ois2wRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o1m(new OISRateHelper(
            0, 1 * Months, Handle<Quote>(ois1mRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o2m(new OISRateHelper(
            0, 2 * Months, Handle<Quote>(ois2mRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o3m(new OISRateHelper(
            0, 3 * Months, Handle<Quote>(ois3mRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o4m(new OISRateHelper(
            0, 4 * Months, Handle<Quote>(ois4mRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o5m(new OISRateHelper(
            0, 5 * Months, Handle<Quote>(ois5mRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o6m(new OISRateHelper(
            0, 6 * Months, Handle<Quote>(ois6mRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o7m(new OISRateHelper(
            0, 7 * Months, Handle<Quote>(ois7mRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o8m(new OISRateHelper(
            0, 8 * Months, Handle<Quote>(ois8mRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o9m(new OISRateHelper(
            0, 9 * Months, Handle<Quote>(ois9mRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o10m(new OISRateHelper(
            0, 10 * Months, Handle<Quote>(ois10mRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o11m(new OISRateHelper(
            0, 11 * Months, Handle<Quote>(ois11mRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o1y(new OISRateHelper(
            0, 1 * Years, Handle<Quote>(ois1yRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o2y(new OISRateHelper(
            0, 2 * Years, Handle<Quote>(ois2yRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o3y(new OISRateHelper(
            0, 3 * Years, Handle<Quote>(ois3yRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o4y(new OISRateHelper(
            0, 4 * Years, Handle<Quote>(ois4yRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o5y(new OISRateHelper(
            0, 5 * Years, Handle<Quote>(ois5yRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o6y(new OISRateHelper(
            0, 6 * Years, Handle<Quote>(ois6yRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o7y(new OISRateHelper(
            0, 7 * Years, Handle<Quote>(ois7yRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o8y(new OISRateHelper(
            0, 8 * Years, Handle<Quote>(ois8yRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o9y(new OISRateHelper(
            0, 9 * Years, Handle<Quote>(ois9yRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o10y(new OISRateHelper(
            0, 10 * Years, Handle<Quote>(ois10yRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o12y(new OISRateHelper(
            0, 12 * Years, Handle<Quote>(ois12yRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o15y(new OISRateHelper(
            0, 15 * Years, Handle<Quote>(ois15yRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o20y(new OISRateHelper(
            0, 20 * Years, Handle<Quote>(ois20yRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o25y(new OISRateHelper(
            0, 25 * Years, Handle<Quote>(ois25yRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o30y(new OISRateHelper(
            0, 30 * Years, Handle<Quote>(ois30yRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o40y(new OISRateHelper(
            0, 40 * Years, Handle<Quote>(ois40yRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o50y(new OISRateHelper(
            0, 50 * Years, Handle<Quote>(ois50yRate), overnightLegIndex));
        boost::shared_ptr<RateHelper> o60y(new OISRateHelper(
            0, 60 * Years, Handle<Quote>(ois60yRate), overnightLegIndex));

        // Any DayCounter would be fine.
        // ActualActual::ISDA ensures that 30 years is 30.0
        DayCounter termStructureDayCounter =
        ActualActual(ActualActual::ISDA);
        
        double tolerance = 1.0e-15;
        
        /********************************
        **  DISCOUNTING CURVE BUILDING **
        *********************************/
		
        // OIS CURVE INSTRUMENTS
        std::vector<boost::shared_ptr<RateHelper> > OisCurveInstruments;
        OisCurveInstruments.push_back(oSw);
        OisCurveInstruments.push_back(o2w);
        OisCurveInstruments.push_back(o1m);
        OisCurveInstruments.push_back(o2m);
        OisCurveInstruments.push_back(o3m);
        OisCurveInstruments.push_back(o4m);
        OisCurveInstruments.push_back(o5m);
        OisCurveInstruments.push_back(o6m);
        OisCurveInstruments.push_back(o7m);
        OisCurveInstruments.push_back(o8m);
        OisCurveInstruments.push_back(o9m);
        OisCurveInstruments.push_back(o10m);
        OisCurveInstruments.push_back(o11m);
        OisCurveInstruments.push_back(o1y);
        OisCurveInstruments.push_back(o2y);
        OisCurveInstruments.push_back(o3y);
        OisCurveInstruments.push_back(o4y);
        OisCurveInstruments.push_back(o5y);
        OisCurveInstruments.push_back(o6y);
        OisCurveInstruments.push_back(o7y);
        OisCurveInstruments.push_back(o8y);
        OisCurveInstruments.push_back(o9y);
        OisCurveInstruments.push_back(o10y);
        OisCurveInstruments.push_back(o12y);
        OisCurveInstruments.push_back(o15y);
        OisCurveInstruments.push_back(o20y);
        OisCurveInstruments.push_back(o25y);
        OisCurveInstruments.push_back(o30y);
        OisCurveInstruments.push_back(o40y);
        OisCurveInstruments.push_back(o50y);
        OisCurveInstruments.push_back(o60y);

        boost::shared_ptr<YieldTermStructure> OisCurve(
                new PiecewiseYieldCurve<Discount, LogCubic>(
                settlementDate, OisCurveInstruments,
                termStructureDayCounter, tolerance,
                LogCubic(CubicInterpolation::Spline, true,
                         CubicInterpolation::SecondDerivative, 0.0,
                         CubicInterpolation::SecondDerivative, 0.0)));

        // Term structures that will be used for discounting cash flows
        RelinkableHandle<YieldTermStructure> discountingTermStructure;
        discountingTermStructure.linkTo(OisCurve);

        /*************************
        *** LIBOR RATE HELPERS ***
        **************************/

        // RateHelpers are built from the above quotes together with
        // other instrument dependant infos.  Quotes are passed in
        // relinkable handles which could be relinked to some other
        // data source later.

        // deposits
        DayCounter depositDayCounter = Actual365Fixed();

        boost::shared_ptr<RateHelper> d1m(new DepositRateHelper(
            Handle<Quote>(d1mRate),
            1*Months, fixingDays,
            calendar, ModifiedFollowing,
            true, depositDayCounter));
        boost::shared_ptr<RateHelper> d2m(new DepositRateHelper(
            Handle<Quote>(d2mRate),
            2 * Months, fixingDays,
            calendar, ModifiedFollowing,
            true, depositDayCounter));
        boost::shared_ptr<RateHelper> d3m(new DepositRateHelper(
            Handle<Quote>(d3mRate),
            3*Months, fixingDays,
            calendar, ModifiedFollowing,
            true, depositDayCounter));

        // setup futures
        // Rate convexityAdjustment = 0.0;
        Integer futMonths = 3;
        boost::shared_ptr<IborIndex> futIndex3M(new GBPLibor(3 * Months));
        Date imm = IMM::nextDate(settlementDate);
        boost::shared_ptr<RateHelper> fut1(new FuturesRateHelper(
            Handle<Quote>(fut1Price),
            imm,
            futIndex3M));
        imm = IMM::nextDate(imm+1);
        boost::shared_ptr<RateHelper> fut2(new FuturesRateHelper(
            Handle<Quote>(fut2Price),
            imm,
            futIndex3M));
        imm = IMM::nextDate(imm+1);
        boost::shared_ptr<RateHelper> fut3(new FuturesRateHelper(
            Handle<Quote>(fut3Price),
            imm,
            futIndex3M));
        imm = IMM::nextDate(imm+1);
        boost::shared_ptr<RateHelper> fut4(new FuturesRateHelper(
            Handle<Quote>(fut4Price),
            imm,
            futIndex3M));
        imm = IMM::nextDate(imm+1);
        boost::shared_ptr<RateHelper> fut5(new FuturesRateHelper(
            Handle<Quote>(fut5Price),
            imm,
            futIndex3M));
        imm = IMM::nextDate(imm+1);
        boost::shared_ptr<RateHelper> fut6(new FuturesRateHelper(
            Handle<Quote>(fut6Price),
            imm,
            futIndex3M));
        imm = IMM::nextDate(imm+1);
        boost::shared_ptr<RateHelper> fut7(new FuturesRateHelper(
            Handle<Quote>(fut7Price),
            imm,
            futIndex3M));
        imm = IMM::nextDate(imm+1);
        boost::shared_ptr<RateHelper> fut8(new FuturesRateHelper(
            Handle<Quote>(fut8Price),
            imm,
            futIndex3M));


        // setup swaps
        Frequency swFixedLegFrequency = Semiannual;
        BusinessDayConvention swFixedLegConvention = ModifiedFollowing;
        DayCounter swFixedLegDayCounter = Actual365Fixed();
        boost::shared_ptr<IborIndex> swFloatingLegIndex(new GBPLibor(3*Months));

        boost::shared_ptr<RateHelper> s3y(new SwapRateHelper(
            Handle<Quote>(s3yRate), 3*Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
			swFloatingLegIndex, Handle<Quote>(), 0 * Days,
			discountingTermStructure));
        boost::shared_ptr<RateHelper> s4y(new SwapRateHelper(
            Handle<Quote>(s4yRate), 4*Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
			swFloatingLegIndex, Handle<Quote>(), 0 * Days,
			discountingTermStructure));
        boost::shared_ptr<RateHelper> s5y(new SwapRateHelper(
            Handle<Quote>(s5yRate), 5*Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
			swFloatingLegIndex, Handle<Quote>(), 0 * Days,
			discountingTermStructure));
        boost::shared_ptr<RateHelper> s6y(new SwapRateHelper(
            Handle<Quote>(s6yRate), 6 * Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
			swFloatingLegIndex, Handle<Quote>(), 0 * Days,
			discountingTermStructure));
        boost::shared_ptr<RateHelper> s7y(new SwapRateHelper(
            Handle<Quote>(s7yRate), 7 * Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
			swFloatingLegIndex, Handle<Quote>(), 0 * Days,
			discountingTermStructure));
        boost::shared_ptr<RateHelper> s8y(new SwapRateHelper(
            Handle<Quote>(s8yRate), 8 * Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
			swFloatingLegIndex, Handle<Quote>(), 0 * Days,
			discountingTermStructure));
        boost::shared_ptr<RateHelper> s9y(new SwapRateHelper(
            Handle<Quote>(s9yRate), 9 * Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
			swFloatingLegIndex, Handle<Quote>(), 0 * Days,
			discountingTermStructure));
        boost::shared_ptr<RateHelper> s10y(new SwapRateHelper(
            Handle<Quote>(s10yRate), 10*Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
            swFloatingLegIndex, Handle<Quote>(), 0 * Days,
            discountingTermStructure));
        boost::shared_ptr<RateHelper> s12y(new SwapRateHelper(
            Handle<Quote>(s12yRate), 12 * Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
            swFloatingLegIndex, Handle<Quote>(), 0 * Days,
            discountingTermStructure));
        boost::shared_ptr<RateHelper> s15y(new SwapRateHelper(
            Handle<Quote>(s15yRate), 15 * Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
            swFloatingLegIndex, Handle<Quote>(), 0 * Days,
            discountingTermStructure));
        boost::shared_ptr<RateHelper> s20y(new SwapRateHelper(
            Handle<Quote>(s20yRate), 20 * Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
            swFloatingLegIndex, Handle<Quote>(), 0 * Days,
            discountingTermStructure));
        boost::shared_ptr<RateHelper> s25y(new SwapRateHelper(
            Handle<Quote>(s25yRate), 25 * Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
            swFloatingLegIndex, Handle<Quote>(), 0 * Days,
            discountingTermStructure));
        boost::shared_ptr<RateHelper> s30y(new SwapRateHelper(
            Handle<Quote>(s30yRate), 30 * Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
            swFloatingLegIndex, Handle<Quote>(), 0 * Days,
            discountingTermStructure));
        boost::shared_ptr<RateHelper> s40y(new SwapRateHelper(
	        Handle<Quote>(s40yRate), 40 * Years,
	        calendar, swFixedLegFrequency,
	        swFixedLegConvention, swFixedLegDayCounter,
	        swFloatingLegIndex, Handle<Quote>(), 0 * Days,
	        discountingTermStructure));
        boost::shared_ptr<RateHelper> s50y(new SwapRateHelper(
            Handle<Quote>(s50yRate), 50 * Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
            swFloatingLegIndex, Handle<Quote>(), 0 * Days,
            discountingTermStructure));
        boost::shared_ptr<RateHelper> s60y(new SwapRateHelper(
            Handle<Quote>(s60yRate), 60 * Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
            swFloatingLegIndex, Handle<Quote>(), 0 * Days,
            discountingTermStructure));


        /***************************
         **  LIBOR CURVE BUILDING **
         ***************************/

        // 3M Libor
        std::vector<boost::shared_ptr<RateHelper> > Libor3mCurveInstruments;
        Libor3mCurveInstruments.push_back(d1m);
        Libor3mCurveInstruments.push_back(d2m);
        Libor3mCurveInstruments.push_back(d3m);
        Libor3mCurveInstruments.push_back(fut1);
        Libor3mCurveInstruments.push_back(fut2);
        Libor3mCurveInstruments.push_back(fut3);
        Libor3mCurveInstruments.push_back(fut4);
        Libor3mCurveInstruments.push_back(fut5);
        Libor3mCurveInstruments.push_back(fut6);
        Libor3mCurveInstruments.push_back(fut7);
        Libor3mCurveInstruments.push_back(fut8);
        Libor3mCurveInstruments.push_back(s3y);
        Libor3mCurveInstruments.push_back(s4y);
        Libor3mCurveInstruments.push_back(s5y);
        Libor3mCurveInstruments.push_back(s6y);
        Libor3mCurveInstruments.push_back(s7y);
        Libor3mCurveInstruments.push_back(s8y);
        Libor3mCurveInstruments.push_back(s9y);
        Libor3mCurveInstruments.push_back(s10y);
        Libor3mCurveInstruments.push_back(s12y);
        Libor3mCurveInstruments.push_back(s15y);
        Libor3mCurveInstruments.push_back(s20y);
        Libor3mCurveInstruments.push_back(s25y);
        Libor3mCurveInstruments.push_back(s30y);
        Libor3mCurveInstruments.push_back(s40y);
        Libor3mCurveInstruments.push_back(s50y);
        Libor3mCurveInstruments.push_back(s60y);

        boost::shared_ptr<YieldTermStructure> Libor3mCurve(
            new PiecewiseYieldCurve<Discount,LogCubic>(
            settlementDate, Libor3mCurveInstruments,
            termStructureDayCounter, tolerance,
            LogCubic(CubicInterpolation::Spline, true,
                     CubicInterpolation::SecondDerivative, 0.0,
                     CubicInterpolation::SecondDerivative, 0.0)));

        // Term structure that will be used for forward rate forecasting
        RelinkableHandle<YieldTermStructure> forecastingTermStructure;
		forecastingTermStructure.linkTo(Libor3mCurve);

        boost::shared_ptr<IborIndex> Libor3MIndex(
            new GBPLibor(3 * Months, forecastingTermStructure));

        /*********************
        * ADD needed Histo Fix *
        **********************/
        Rate fix = 0.0038275;
        Libor3MIndex->addFixing(Date(30, September, 2016), fix);
        fix = 0.0046056;
        Libor3MIndex->addFixing(Date(29, July, 2016), fix);

        /*********************
        * SWAP 1 TO BE PRICED *
        **********************/

        // constant nominal 17,500,000 GBP
        Real nominal = 17500000.0;
        VanillaSwap::Type swapType = VanillaSwap::Receiver; //party A receives the fix
        Date startdate(30, September, 2015);
        Date endtdate(31, December, 2018);

        // fixed leg (Party B)
        Frequency fixedLegFrequency = Quarterly;
        BusinessDayConvention fixedLegConvention = ModifiedFollowing;
        DayCounter fixedLegDayCounter = Actual365Fixed();
        Rate fixedRate = 0.02465;

        // floating leg (Party A)
        Frequency floatingLegFrequency = Quarterly;
        BusinessDayConvention floatingLegConvention = ModifiedFollowing;
        DayCounter floatingLegDayCounter = Actual365Fixed();
        Spread spread = 0.0;

        //schedule definition
        Schedule fixedSchedule(startdate, endtdate,
                               Period(fixedLegFrequency),
                               calendar, fixedLegConvention,
                               fixedLegConvention,
                               DateGeneration::Backward, true);
        Schedule floatSchedule(startdate, endtdate,
                               Period(floatingLegFrequency),
                               calendar, floatingLegConvention,
                               floatingLegConvention,
                               DateGeneration::Backward, true);

		// swap creation
        VanillaSwap Swap1(swapType, nominal,
            fixedSchedule, fixedRate, fixedLegDayCounter,
            floatSchedule, Libor3MIndex, spread,
            floatingLegDayCounter);

        
        //pricing engine for the swap
        boost::shared_ptr<PricingEngine> swapEngine(
          new DiscountingSwapEngine(discountingTermStructure));
        
		/***************
        * SWAP 1 PRICING *
        ****************/

        Swap1.setPricingEngine(swapEngine);

        Real NPV;
        Rate fairRate;
        Spread fairSpread;

        NPV = Swap1.NPV();
        fairSpread = Swap1.fairSpread();
        fairRate = Swap1.fairRate();

        /*******************
        * SWAP 1 REPORTING *
        ********************/

        // utilities for reporting
        std::vector<std::string> headers(4);
        headers[0] = "term structure";
        headers[1] = "net present value";
        headers[2] = "fair spread";
        headers[3] = "fair fixed rate";
        std::string separator = " | ";
        Size width = headers[0].size() + separator.size()
                   + headers[1].size() + separator.size()
                   + headers[2].size() + separator.size()
                   + headers[3].size() + separator.size() - 1;
        std::string rule(width, '-'), dblrule(width, '=');
        std::string tab(8, ' ');

        // swap 1
        std::cout << tab << "swap 1 paying "
                  << io::rate(fixedRate) << std::endl;
        std::cout << headers[0] << separator
                  << headers[1] << separator
                  << headers[2] << separator
                  << headers[3] << separator << std::endl;
        std::cout << rule << std::endl;

        std::cout << std::setw(headers[0].size())
                  << "ois-discounting" << separator;
        std::cout << std::setw(headers[1].size())
                  << std::fixed << std::setprecision(2) << NPV << separator;
        std::cout << std::setw(headers[2].size())
                  << io::rate(fairSpread) << separator;
        std::cout << std::setw(headers[3].size())
                  << io::rate(fairRate) << separator;
        std::cout << std::endl;
        std::cout << rule << std::endl;

        /*********************
        * SWAP 2 TO BE PRICED *
        **********************/

        // constant nominal 10000,000 GBP
        Real nominal2 = 10000000.0;
        VanillaSwap::Type swapType2 = VanillaSwap::Receiver; //party A receives the fix
        Date startdate2(04, January, 2013);
        Date endtdate2(31, January, 2017);

        // fixed leg (Party B)
        Frequency fixedLegFrequency2 = Quarterly;
        BusinessDayConvention fixedLegConvention2 = ModifiedFollowing;
        DayCounter fixedLegDayCounter2 = Actual365Fixed();
        Rate fixedRate2 = 0.00993;

        // floating leg (Party A)
        Frequency floatingLegFrequency2 = Quarterly;
        BusinessDayConvention floatingLegConvention2 = ModifiedFollowing;
        DayCounter floatingLegDayCounter2 = Actual365Fixed();
        Spread spread2 = 0.0;

        //schedule definition
        Schedule fixedSchedule2(startdate2, endtdate2,
            Period(fixedLegFrequency2),
            calendar, fixedLegConvention2,
            fixedLegConvention2,
            DateGeneration::Backward, true);
        Schedule floatSchedule2(startdate2, endtdate2,
            Period(floatingLegFrequency2),
            calendar, floatingLegConvention2,
            floatingLegConvention2,
            DateGeneration::Backward, true);

        // swap creation
        VanillaSwap Swap2(swapType2, nominal2,
            fixedSchedule2, fixedRate2, fixedLegDayCounter2,
            floatSchedule2, Libor3MIndex, spread2,
            floatingLegDayCounter2);

        /***************
        * SWAP 2 PRICING *
        ****************/

        Swap2.setPricingEngine(swapEngine);

        Real NPV2;
        Rate fairRate2;
        Spread fairSpread2;

        NPV2 = Swap2.NPV();
        fairSpread2 = Swap2.fairSpread();
        fairRate2 = Swap2.fairRate();

        /*******************
        * SWAP 2 REPORTING *
        ********************/

        // swap 2
        std::cout << tab << "swap 2 paying "
            << io::rate(fixedRate2) << std::endl;
        std::cout << headers[0] << separator
            << headers[1] << separator
            << headers[2] << separator
            << headers[3] << separator << std::endl;
        std::cout << rule << std::endl;

        std::cout << std::setw(headers[0].size())
            << "ois-discounting" << separator;
        std::cout << std::setw(headers[1].size())
            << std::fixed << std::setprecision(2) 
            << NPV2 << separator;
        std::cout << std::setw(headers[2].size())
            << io::rate(fairSpread2) << separator;
        std::cout << std::setw(headers[3].size())
            << io::rate(fairRate2) << separator;
        std::cout << std::endl;
        std::cout << rule << std::endl;

        /************************
        * PERFORMANCE REPORTING *
        *************************/

        double seconds = timer.elapsed();
        Integer hours = int(seconds/3600);
        seconds -= hours * 3600;
        Integer minutes = int(seconds/60);
        seconds -= minutes * 60;
        std::cout << " \nRun completed in ";
        if (hours > 0)
            std::cout << hours << " h ";
        if (hours > 0 || minutes > 0)
            std::cout << minutes << " m ";
        std::cout << std::fixed << std::setprecision(0)
                  << seconds << " s\n" << std::endl;

        return 0;

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
        return 1;
    }
}

