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
        Date settlementDate(04, October, 2016);
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
        Rate donQuote = 0.0;
        //OIS
        Rate oisSWQuote = 0.0;
        Rate ois2WQuote = 0.0;
        Rate ois1MQuote = 0.0;
        Rate ois2MQuote = 0.0;
        Rate ois3MQuote = 0.0;
        Rate ois4MQuote = 0.0;
        Rate ois5MQuote = 0.0;
        Rate ois6MQuote = 0.0;
        Rate ois7MQuote = 0.0;
        Rate ois8MQuote = 0.0;
        Rate ois9MQuote = 0.0;
        Rate ois10MQuote = 0.0;
        Rate ois11MQuote = 0.0;
        Rate ois1yQuote = 0.0;
        Rate ois2yQuote = 0.0;
        Rate ois3yQuote = 0.0;
        Rate ois4yQuote = 0.0;
        Rate ois5yQuote = 0.0;
        Rate ois6yQuote = 0.0;
        Rate ois7yQuote = 0.0;
        Rate ois8yQuote = 0.0;
        Rate ois9yQuote = 0.0;
        Rate ois10yQuote = 0.0;

        // 3 Months Libor Instruments
        // synth deposits
        Rate d1mQuote = 0.0;
        Rate d2mQuote = 0.0;
        Rate d3mQuote = 0.0;
        // futures
        Real fut1Quote = 100;
        Real fut2Quote = 100;
        Real fut3Quote = 100;
        Real fut4Quote = 100;
        Real fut5Quote = 100;
        Real fut6Quote = 100;
        Real fut7Quote = 100;
        Real fut8Quote = 100;
        // swaps
        Rate s3yQuote = 0.0;
        Rate s4yQuote = 0.0;
        Rate s5yQuote = 0.0;
        Rate s6yQuote = 0.0;
        Rate s7yQuote = 0.0;
        Rate s8yQuote = 0.0;
        Rate s9yQuote = 0.0;
        Rate s10yQuote = 0.0;


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
		Rate oisSWQuote = 0.0;
		boost::shared_ptr<Quote> oisSWRate(new SimpleQuote(oisSWQuote));
        boost::shared_ptr<Quote> ois2WRate(new SimpleQuote(ois2WQuote));
        boost::shared_ptr<Quote> ois1MRate(new SimpleQuote(ois1MQuote));
        boost::shared_ptr<Quote> ois2MRate(new SimpleQuote(ois2MQuote));
        boost::shared_ptr<Quote> ois3MRate(new SimpleQuote(ois3MQuote));
        boost::shared_ptr<Quote> ois4MRate(new SimpleQuote(ois4MQuote));
        boost::shared_ptr<Quote> ois5MRate(new SimpleQuote(ois5MQuote));
        boost::shared_ptr<Quote> ois6MRate(new SimpleQuote(ois6MQuote));
        boost::shared_ptr<Quote> ois7MRate(new SimpleQuote(ois7MQuote));
        boost::shared_ptr<Quote> ois8MRate(new SimpleQuote(ois8MQuote));
        boost::shared_ptr<Quote> ois9MRate(new SimpleQuote(ois9MQuote));
        boost::shared_ptr<Quote> ois10MRate(new SimpleQuote(ois10MQuote));
        boost::shared_ptr<Quote> ois11MRate(new SimpleQuote(ois11MQuote));
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


        /*********************
         ***  RATE HELPERS ***
         *********************/

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
        BusinessDayConvention swFixedLegConvention = Unadjusted;
        DayCounter swFixedLegDayCounter = Actual365Fixed();
        boost::shared_ptr<IborIndex> swFloatingLegIndex(new GBPLibor(3*Months));

        boost::shared_ptr<RateHelper> s3y(new SwapRateHelper(
            Handle<Quote>(s3yRate), 3*Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
            swFloatingLegIndex));
        boost::shared_ptr<RateHelper> s4y(new SwapRateHelper(
            Handle<Quote>(s4yRate), 4*Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
            swFloatingLegIndex));
        boost::shared_ptr<RateHelper> s5y(new SwapRateHelper(
            Handle<Quote>(s5yRate), 5*Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
            swFloatingLegIndex));
        boost::shared_ptr<RateHelper> s6y(new SwapRateHelper(
            Handle<Quote>(s6yRate), 6 * Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
            swFloatingLegIndex));
        boost::shared_ptr<RateHelper> s7y(new SwapRateHelper(
            Handle<Quote>(s7yRate), 7 * Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
            swFloatingLegIndex));
        boost::shared_ptr<RateHelper> s8y(new SwapRateHelper(
            Handle<Quote>(s8yRate), 8 * Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
            swFloatingLegIndex));
        boost::shared_ptr<RateHelper> s9y(new SwapRateHelper(
            Handle<Quote>(s9yRate), 9 * Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
            swFloatingLegIndex));
        boost::shared_ptr<RateHelper> s10y(new SwapRateHelper(
            Handle<Quote>(s10yRate), 10*Years,
            calendar, swFixedLegFrequency,
            swFixedLegConvention, swFixedLegDayCounter,
            swFloatingLegIndex));


        /*********************
         **  CURVE BUILDING **
         *********************/

        // Any DayCounter would be fine.
        // ActualActual::ISDA ensures that 30 years is 30.0
        DayCounter termStructureDayCounter =
            ActualActual(ActualActual::ISDA);


        double tolerance = 1.0e-15;

        // 3M Libor
        std::vector<boost::shared_ptr<RateHelper> > LiborCurveInstruments;
        LiborCurveInstruments.push_back(d1m);
        LiborCurveInstruments.push_back(d2m);
        LiborCurveInstruments.push_back(d3m);
        LiborCurveInstruments.push_back(fut1);
        LiborCurveInstruments.push_back(fut2);
        LiborCurveInstruments.push_back(fut3);
        LiborCurveInstruments.push_back(fut4);
        LiborCurveInstruments.push_back(fut5);
        LiborCurveInstruments.push_back(fut6);
        LiborCurveInstruments.push_back(fut7);
        LiborCurveInstruments.push_back(fut8);
        LiborCurveInstruments.push_back(s3y);
        LiborCurveInstruments.push_back(s4y);
        LiborCurveInstruments.push_back(s5y);
        LiborCurveInstruments.push_back(s6y);
        LiborCurveInstruments.push_back(s7y);
        LiborCurveInstruments.push_back(s8y);
        LiborCurveInstruments.push_back(s9y);
        LiborCurveInstruments.push_back(s10y);
        boost::shared_ptr<YieldTermStructure> LiborCurve(
            new PiecewiseYieldCurve<Discount,LogLinear>(
                                          settlementDate, LiborCurveInstruments,
                                          termStructureDayCounter,
                                          tolerance));

        // Term structures that will be used for pricing:
        // the one used for discounting cash flows
        RelinkableHandle<YieldTermStructure> discountingTermStructure;
        // the one used for forward rate forecasting
        RelinkableHandle<YieldTermStructure> forecastingTermStructure;


        /*********************
        * SWAPS TO BE PRICED *
        **********************/

        // constant nominal 1,000,000 Euro
        Real nominal = 1000000.0;
        // fixed leg
        Frequency fixedLegFrequency = Annual;
        BusinessDayConvention fixedLegConvention = Unadjusted;
        BusinessDayConvention floatingLegConvention = ModifiedFollowing;
        DayCounter fixedLegDayCounter = Thirty360(Thirty360::European);
        Rate fixedRate = 0.04;
        DayCounter floatingLegDayCounter = Actual360();

        // floating leg
        Frequency floatingLegFrequency = Semiannual;
        boost::shared_ptr<IborIndex> euriborIndex(
                                     new Euribor6M(forecastingTermStructure));
        Spread spread = 0.0;

        Integer lenghtInYears = 5;
        VanillaSwap::Type swapType = VanillaSwap::Payer;

        Date maturity = settlementDate + lenghtInYears*Years;
        Schedule fixedSchedule(settlementDate, maturity,
                               Period(fixedLegFrequency),
                               calendar, fixedLegConvention,
                               fixedLegConvention,
                               DateGeneration::Forward, false);
        Schedule floatSchedule(settlementDate, maturity,
                               Period(floatingLegFrequency),
                               calendar, floatingLegConvention,
                               floatingLegConvention,
                               DateGeneration::Forward, false);
        VanillaSwap spot5YearSwap(swapType, nominal,
            fixedSchedule, fixedRate, fixedLegDayCounter,
            floatSchedule, euriborIndex, spread,
            floatingLegDayCounter);

        Date fwdStart = calendar.advance(settlementDate, 1, Years);
        Date fwdMaturity = fwdStart + lenghtInYears*Years;
        Schedule fwdFixedSchedule(fwdStart, fwdMaturity,
                                  Period(fixedLegFrequency),
                                  calendar, fixedLegConvention,
                                  fixedLegConvention,
                                  DateGeneration::Forward, false);
        Schedule fwdFloatSchedule(fwdStart, fwdMaturity,
                                  Period(floatingLegFrequency),
                                  calendar, floatingLegConvention,
                                  floatingLegConvention,
                                  DateGeneration::Forward, false);
        VanillaSwap oneYearForward5YearSwap(swapType, nominal,
            fwdFixedSchedule, fixedRate, fixedLegDayCounter,
            fwdFloatSchedule, euriborIndex, spread,
            floatingLegDayCounter);


        /***************
        * SWAP PRICING *
        ****************/

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

        // calculations
        std::cout << dblrule << std::endl;
        std::cout <<  "5-year market swap-rate = "
                  << std::setprecision(2) << io::rate(s5yRate->value())
                  << std::endl;
        std::cout << dblrule << std::endl;

        std::cout << tab << "5-years swap paying "
                  << io::rate(fixedRate) << std::endl;
        std::cout << headers[0] << separator
                  << headers[1] << separator
                  << headers[2] << separator
                  << headers[3] << separator << std::endl;
        std::cout << rule << std::endl;

        Real NPV;
        Rate fairRate;
        Spread fairSpread;

        boost::shared_ptr<PricingEngine> swapEngine(
                         new DiscountingSwapEngine(discountingTermStructure));

        spot5YearSwap.setPricingEngine(swapEngine);
        oneYearForward5YearSwap.setPricingEngine(swapEngine);

        // Of course, you're not forced to really use different curves
        forecastingTermStructure.linkTo(LiborCurve);
        discountingTermStructure.linkTo(LiborCurve);

        NPV = spot5YearSwap.NPV();
        fairSpread = spot5YearSwap.fairSpread();
        fairRate = spot5YearSwap.fairRate();

        std::cout << std::setw(headers[0].size())
                  << "depo-swap" << separator;
        std::cout << std::setw(headers[1].size())
                  << std::fixed << std::setprecision(2) << NPV << separator;
        std::cout << std::setw(headers[2].size())
                  << io::rate(fairSpread) << separator;
        std::cout << std::setw(headers[3].size())
                  << io::rate(fairRate) << separator;
        std::cout << std::endl;


        // let's check that the 5 years swap has been correctly re-priced
        QL_REQUIRE(std::fabs(fairRate-s5yQuote)<1e-8,
                   "5-years swap mispriced by "
                   << io::rate(std::fabs(fairRate-s5yQuote)));


        forecastingTermStructure.linkTo(LiborCurve);
        discountingTermStructure.linkTo(LiborCurve);

        NPV = spot5YearSwap.NPV();
        fairSpread = spot5YearSwap.fairSpread();
        fairRate = spot5YearSwap.fairRate();

        std::cout << std::setw(headers[0].size())
                  << "depo-fut-swap" << separator;
        std::cout << std::setw(headers[1].size())
                  << std::fixed << std::setprecision(2) << NPV << separator;
        std::cout << std::setw(headers[2].size())
                  << io::rate(fairSpread) << separator;
        std::cout << std::setw(headers[3].size())
                  << io::rate(fairRate) << separator;
        std::cout << std::endl;

        QL_REQUIRE(std::fabs(fairRate-s5yQuote)<1e-8,
                   "5-years swap mispriced!");


        forecastingTermStructure.linkTo(LiborCurve);
        discountingTermStructure.linkTo(LiborCurve);

        NPV = spot5YearSwap.NPV();
        fairSpread = spot5YearSwap.fairSpread();
        fairRate = spot5YearSwap.fairRate();

        std::cout << std::setw(headers[0].size())
                  << "depo-FRA-swap" << separator;
        std::cout << std::setw(headers[1].size())
                  << std::fixed << std::setprecision(2) << NPV << separator;
        std::cout << std::setw(headers[2].size())
                  << io::rate(fairSpread) << separator;
        std::cout << std::setw(headers[3].size())
                  << io::rate(fairRate) << separator;
        std::cout << std::endl;

        QL_REQUIRE(std::fabs(fairRate-s5yQuote)<1e-8,
                   "5-years swap mispriced!");


        std::cout << rule << std::endl;

        // now let's price the 1Y forward 5Y swap

        std::cout << tab << "5-years, 1-year forward swap paying "
                  << io::rate(fixedRate) << std::endl;
        std::cout << headers[0] << separator
                  << headers[1] << separator
                  << headers[2] << separator
                  << headers[3] << separator << std::endl;
        std::cout << rule << std::endl;


        forecastingTermStructure.linkTo(LiborCurve);
        discountingTermStructure.linkTo(LiborCurve);

        NPV = oneYearForward5YearSwap.NPV();
        fairSpread = oneYearForward5YearSwap.fairSpread();
        fairRate = oneYearForward5YearSwap.fairRate();

        std::cout << std::setw(headers[0].size())
                  << "depo-swap" << separator;
        std::cout << std::setw(headers[1].size())
                  << std::fixed << std::setprecision(2) << NPV << separator;
        std::cout << std::setw(headers[2].size())
                  << io::rate(fairSpread) << separator;
        std::cout << std::setw(headers[3].size())
                  << io::rate(fairRate) << separator;
        std::cout << std::endl;


        forecastingTermStructure.linkTo(LiborCurve);
        discountingTermStructure.linkTo(LiborCurve);

        NPV = oneYearForward5YearSwap.NPV();
        fairSpread = oneYearForward5YearSwap.fairSpread();
        fairRate = oneYearForward5YearSwap.fairRate();

        std::cout << std::setw(headers[0].size())
                  << "depo-fut-swap" << separator;
        std::cout << std::setw(headers[1].size())
                  << std::fixed << std::setprecision(2) << NPV << separator;
        std::cout << std::setw(headers[2].size())
                  << io::rate(fairSpread) << separator;
        std::cout << std::setw(headers[3].size())
                  << io::rate(fairRate) << separator;
        std::cout << std::endl;


        forecastingTermStructure.linkTo(LiborCurve);
        discountingTermStructure.linkTo(LiborCurve);

        NPV = oneYearForward5YearSwap.NPV();
        fairSpread = oneYearForward5YearSwap.fairSpread();
        fairRate = oneYearForward5YearSwap.fairRate();

        std::cout << std::setw(headers[0].size())
                  << "depo-FRA-swap" << separator;
        std::cout << std::setw(headers[1].size())
                  << std::fixed << std::setprecision(2) << NPV << separator;
        std::cout << std::setw(headers[2].size())
                  << io::rate(fairSpread) << separator;
        std::cout << std::setw(headers[3].size())
                  << io::rate(fairRate) << separator;
        std::cout << std::endl;


        // now let's say that the 5-years swap rate goes up to 4.60%.
        // A smarter market element--say, connected to a data source-- would
        // notice the change itself. Since we're using SimpleQuotes,
        // we'll have to change the value manually--which forces us to
        // downcast the handle and use the SimpleQuote
        // interface. In any case, the point here is that a change in the
        // value contained in the Quote triggers a new bootstrapping
        // of the curve and a repricing of the swap.

        boost::shared_ptr<SimpleQuote> fiveYearsRate =
            boost::dynamic_pointer_cast<SimpleQuote>(s5yRate);
        fiveYearsRate->setValue(0.0460);

        std::cout << dblrule << std::endl;
        std::cout <<  "5-year market swap-rate = "
                  << io::rate(s5yRate->value()) << std::endl;
        std::cout << dblrule << std::endl;

        std::cout << tab << "5-years swap paying "
                  << io::rate(fixedRate) << std::endl;
        std::cout << headers[0] << separator
                  << headers[1] << separator
                  << headers[2] << separator
                  << headers[3] << separator << std::endl;
        std::cout << rule << std::endl;

        // now get the updated results
        forecastingTermStructure.linkTo(LiborCurve);
        discountingTermStructure.linkTo(LiborCurve);

        NPV = spot5YearSwap.NPV();
        fairSpread = spot5YearSwap.fairSpread();
        fairRate = spot5YearSwap.fairRate();

        std::cout << std::setw(headers[0].size())
                  << "depo-swap" << separator;
        std::cout << std::setw(headers[1].size())
                  << std::fixed << std::setprecision(2) << NPV << separator;
        std::cout << std::setw(headers[2].size())
                  << io::rate(fairSpread) << separator;
        std::cout << std::setw(headers[3].size())
                  << io::rate(fairRate) << separator;
        std::cout << std::endl;

        QL_REQUIRE(std::fabs(fairRate-s5yRate->value())<1e-8,
                   "5-years swap mispriced!");


        forecastingTermStructure.linkTo(LiborCurve);
        discountingTermStructure.linkTo(LiborCurve);

        NPV = spot5YearSwap.NPV();
        fairSpread = spot5YearSwap.fairSpread();
        fairRate = spot5YearSwap.fairRate();

        std::cout << std::setw(headers[0].size())
                  << "depo-fut-swap" << separator;
        std::cout << std::setw(headers[1].size())
                  << std::fixed << std::setprecision(2) << NPV << separator;
        std::cout << std::setw(headers[2].size())
                  << io::rate(fairSpread) << separator;
        std::cout << std::setw(headers[3].size())
                  << io::rate(fairRate) << separator;
        std::cout << std::endl;

        QL_REQUIRE(std::fabs(fairRate-s5yRate->value())<1e-8,
                   "5-years swap mispriced!");


        forecastingTermStructure.linkTo(LiborCurve);
        discountingTermStructure.linkTo(LiborCurve);

        NPV = spot5YearSwap.NPV();
        fairSpread = spot5YearSwap.fairSpread();
        fairRate = spot5YearSwap.fairRate();

        std::cout << std::setw(headers[0].size())
                  << "depo-FRA-swap" << separator;
        std::cout << std::setw(headers[1].size())
                  << std::fixed << std::setprecision(2) << NPV << separator;
        std::cout << std::setw(headers[2].size())
                  << io::rate(fairSpread) << separator;
        std::cout << std::setw(headers[3].size())
                  << io::rate(fairRate) << separator;
        std::cout << std::endl;

        QL_REQUIRE(std::fabs(fairRate-s5yRate->value())<1e-8,
                   "5-years swap mispriced!");

        std::cout << rule << std::endl;

        // the 1Y forward 5Y swap changes as well

        std::cout << tab << "5-years, 1-year forward swap paying "
                  << io::rate(fixedRate) << std::endl;
        std::cout << headers[0] << separator
                  << headers[1] << separator
                  << headers[2] << separator
                  << headers[3] << separator << std::endl;
        std::cout << rule << std::endl;


        forecastingTermStructure.linkTo(LiborCurve);
        discountingTermStructure.linkTo(LiborCurve);

        NPV = oneYearForward5YearSwap.NPV();
        fairSpread = oneYearForward5YearSwap.fairSpread();
        fairRate = oneYearForward5YearSwap.fairRate();

        std::cout << std::setw(headers[0].size())
                  << "depo-swap" << separator;
        std::cout << std::setw(headers[1].size())
                  << std::fixed << std::setprecision(2) << NPV << separator;
        std::cout << std::setw(headers[2].size())
                  << io::rate(fairSpread) << separator;
        std::cout << std::setw(headers[3].size())
                  << io::rate(fairRate) << separator;
        std::cout << std::endl;


        forecastingTermStructure.linkTo(LiborCurve);
        discountingTermStructure.linkTo(LiborCurve);

        NPV = oneYearForward5YearSwap.NPV();
        fairSpread = oneYearForward5YearSwap.fairSpread();
        fairRate = oneYearForward5YearSwap.fairRate();

        std::cout << std::setw(headers[0].size())
                  << "depo-fut-swap" << separator;
        std::cout << std::setw(headers[1].size())
                  << std::fixed << std::setprecision(2) << NPV << separator;
        std::cout << std::setw(headers[2].size())
                  << io::rate(fairSpread) << separator;
        std::cout << std::setw(headers[3].size())
                  << io::rate(fairRate) << separator;
        std::cout << std::endl;


        forecastingTermStructure.linkTo(LiborCurve);
        discountingTermStructure.linkTo(LiborCurve);

        NPV = oneYearForward5YearSwap.NPV();
        fairSpread = oneYearForward5YearSwap.fairSpread();
        fairRate = oneYearForward5YearSwap.fairRate();

        std::cout << std::setw(headers[0].size())
                  << "depo-FRA-swap" << separator;
        std::cout << std::setw(headers[1].size())
                  << std::fixed << std::setprecision(2) << NPV << separator;
        std::cout << std::setw(headers[2].size())
                  << io::rate(fairSpread) << separator;
        std::cout << std::setw(headers[3].size())
                  << io::rate(fairRate) << separator;
        std::cout << std::endl;

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

