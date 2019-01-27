/*
 *  Created by Phil Nash on 26/6/2018.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef TWOBLUECUBES_CATCH_INTERFACES_GENERATORTRACKER_INCLUDED
#define TWOBLUECUBES_CATCH_INTERFACES_GENERATORTRACKER_INCLUDED

#include <memory>

namespace Catch {

    namespace Generators {
        class GeneratorUntypedBase {
        private:

        public:
            GeneratorUntypedBase() = default;
            virtual ~GeneratorUntypedBase();
            virtual bool next() = 0;
        };
        using GeneratorBasePtr = std::unique_ptr<GeneratorUntypedBase>;

    } // namespace Generators

    struct IGeneratorTracker {
        virtual ~IGeneratorTracker();
        virtual auto hasGenerator() const -> bool = 0;
        virtual auto getGenerator() const -> Generators::GeneratorBasePtr const& = 0;
        virtual void setGenerator( Generators::GeneratorBasePtr&& generator ) = 0;
    };

} // namespace Catch

#endif //TWOBLUECUBES_CATCH_INTERFACES_GENERATORTRACKER_INCLUDED
