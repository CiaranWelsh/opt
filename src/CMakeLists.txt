set(target opt)
add_library(${target} STATIC
        Optimizer
        PopulationOptimizer
        GeneticAlgorithm
        RandomNumberGenerator
        OptItem
        OptItems
        Error
        CrossOver
        Mutation
        Selection
        Population
        Individual
        BlockingQueue
        TourneySelection
        BasicMutation
        IntermediateRecombination
        Operator
        )
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})



#set(target SRESC)
#add_library(${target} SHARED CSRES.cpp CSRES.h)
#target_link_libraries(${target} PUBLIC SRES)


install(
        TARGETS opt
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)









