set(target SRES)
add_library(${target} STATIC
        Optimizer
        EvolutionaryOptimizer
        GeneticAlgorithm
        SRES
        RandomNumberGenerator
        OptItem
        OptItems
        Error
        SRESRevamped
        Replicate
        Mutate
        Select
        Population
        Individual
        BlockingQueue
        )
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})



set(target SRESC)
add_library(${target} SHARED CSRES.cpp CSRES.h)
target_link_libraries(${target} PUBLIC SRES)


install(
        TARGETS SRES SRESC
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)









