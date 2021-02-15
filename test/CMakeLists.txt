include(GoogleTest)


function(add_test_executable BINARY OUT_VARIABLE)
    add_executable(${BINARY} ${ARGN})

    target_include_directories(${BINARY} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
    target_link_libraries(${BINARY} PUBLIC opt gtest gtest_main gmock gmock_main)

    set_target_properties(${BINARY} PROPERTIES LINKER_LANGUAGE CXX)

    if ("${${OUT_VARIABLE}}" STREQUAL "")
        set(${OUT_VARIABLE} "${BINARY}" PARENT_SCOPE)
    else ()
        set(${OUT_VARIABLE} "${${OUT_VARIABLE}}" "${BINARY}" PARENT_SCOPE)
    endif ()

endfunction()

set(TESTS)
add_test_executable(SRES-BealeFunction TESTS BealeFunction.cpp)
add_test_executable(RNGTests TESTS RNGTests.cpp)
add_test_executable(OptItemsTest TESTS OptItemsTest.cpp)
add_test_executable(OptItemTest TESTS OptItemTest.cpp)
add_test_executable(GeneticAlgorithmIntegrationTests TESTS GeneticAlgorithmIntegrationTests.cpp)
add_test_executable(TournanentSelectionTests.cpp TESTS TournanentSelectionTests.cpp)
add_test_executable(PopulationTests TESTS PopulationTests.cpp)
add_test_executable(IndividualTests TESTS IndividualTests.cpp CostFunctions.h)
add_test_executable(ContainerTests TESTS ContainerTests.cpp )
add_test_executable(CxOnePointTests TESTS CxOnePointTests.cpp MockPopulationOptimizer.h)
add_test_executable(SimpleRNG TESTS SimpleRNG.cpp)
add_test_executable(EvaluationThreading TESTS EvaluationThreading.cpp)
add_test_executable(PointMutationTests TESTS PointMutationTests.cpp)




install(TARGETS ${TESTS})











