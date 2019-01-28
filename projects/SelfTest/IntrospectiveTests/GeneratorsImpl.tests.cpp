#include "catch.hpp"

// Tests of generator implementation details
TEST_CASE("Generators internals", "[generators][internals]") {
    using namespace Catch::Generators;

    SECTION("Single value") {
        auto gen = value(123);
        REQUIRE(gen.get() == 123);
        REQUIRE_FALSE(gen.next());
    }
    SECTION("Preset values") {
        auto gen = values({ 1, 3, 5 });
        REQUIRE(gen.get() == 1);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 3);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 5);
        REQUIRE_FALSE(gen.next());
    }
    SECTION("Generator combinator") {
        auto gen = makeGenerators(1, 5, values({ 2, 4 }), 0);
        REQUIRE(gen.get() == 1);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 5);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 2);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 4);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 0);
        REQUIRE_FALSE(gen.next());
    }
    SECTION("Explicitly typed generator sequence") {
        auto gen = makeGenerators(as<std::string>{}, "aa", "bb", "cc");
        // This just checks that the type is std::string:
        REQUIRE(gen.get().size() == 2);
        // Iterate over the generator
        REQUIRE(gen.get() == "aa");
        REQUIRE(gen.next());
        REQUIRE(gen.get() == "bb");
        REQUIRE(gen.next());
        REQUIRE(gen.get() == "cc");
        REQUIRE_FALSE(gen.next());
    }
    SECTION("Filter generator") {
        // Normal usage
        auto gen = filter([] (int i) { return i != 2; }, values({ 2, 1, 2, 3, 2, 2 }));
        REQUIRE(gen.get() == 1);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 3);
        REQUIRE_FALSE(gen.next());

        // Completely filtered-out generator should throw on construction
        REQUIRE_THROWS_AS(filter([] (int) { return false; }, value(1)), Catch::GeneratorException);
    }
    SECTION("Take generator") {
        SECTION("Take less") {
            auto gen = take(2, values({ 1, 2, 3 }));
            REQUIRE(gen.get() == 1);
            REQUIRE(gen.next());
            REQUIRE(gen.get() == 2);
            REQUIRE_FALSE(gen.next());
        }
        SECTION("Take more") {
            auto gen = take(2, value(1));
            REQUIRE(gen.get() == 1);
            REQUIRE_FALSE(gen.next());
        }
    }
}
