
/*
 Copyright (C) 2006 Eric Ehlers

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email quantlib-dev@lists.sf.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <qlxl/Conversions/coercequotehandle.hpp>

#include <oh/object.hpp>
#include <oh/objecthandler.hpp>
#include <ohxl/Conversions/opertoscalar.hpp>
#include <ql/Quotes/simplequote.hpp>
#include <qlo/Conversions/coercehandle.hpp>
#include <qlo/quotes.hpp>

namespace ObjHandler {

    bool operToQuoteHandle(
            const OPER &in,
            QuantLib::RelinkableHandle<QuantLib::Quote> &out) {

        OH_REQUIRE(!(in.xltype & xltypeErr), 
            "input value has type=error");

        if (in.xltype & xltypeNum) {
            out.linkTo(boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(in.val.num)));
            return true;
        } else if (in.xltype & xltypeStr) {
            std::string id;
            operToScalar(in, id);
            OH_GET_OBJECT(temp, id, ObjHandler::Object)
            out = CoerceHandle<QuantLibAddin::Quote, QuantLib::Quote>()(temp);
            return true;
        } else {
            return false;
        }
    }

    bool CoerceQuoteHandle::inputMissing(const OPER &in) {
        return ((in.xltype & xltypeNil)
            ||  (in.xltype & xltypeMissing)
            || ((in.xltype & xltypeErr) && (in.val.err == xlerrNA)));
    }

}
