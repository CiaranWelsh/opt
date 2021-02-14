set(target opt)
add_library(${target} STATIC
        RandomNumberGenerator
        Optimizer
            PopulationOptimizer
            GeneticAlgorithm
        Container.h
            Population
            Individual
        OptItem
        OptItems
        Error
        BlockingQueue
        Operator
        CrossOver
            CxOnePoint
            IntermediateRecombination
        Mutation
            BasicMutation
        Selection
            TourneySelection
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









