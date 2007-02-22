
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

#ifndef qlxl_conversions_coercequotehandle_hpp
#define qlxl_conversions_coercequotehandle_hpp

#include <oh/Conversions/coerce.hpp>
#include <oh/objhandlerdefines.hpp>
#include <xlsdk/xlsdkdefines.hpp>
#include <ql/handle.hpp>
#include <ql/quote.hpp>

namespace ObjHandler {

    bool operToQuoteHandle(
            const OPER &in,
            QuantLib::RelinkableHandle<QuantLib::Quote> &out);

    class CoerceQuoteHandle : public ObjHandler::Coerce<
            OPER, 
            QuantLib::RelinkableHandle<QuantLib::Quote> > {
        Conversion *getConversions() {
            static Conversion conversions[] = {
                operToQuoteHandle,
                0
            };
            return conversions; 
        };
        virtual bool inputMissing(const OPER&);
    };

}

#endif
