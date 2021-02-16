set(target opt)
add_library(${target} STATIC
        RandomNumberGenerator
        Optimizer
            PopulationOptimizer
            GeneticAlgorithm
            DiffEvolution
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
            DiffEvolutionCxBinomial
        Mutation
            BasicMutation
            PointMutation
            DiffEvolutionMutation1
        Selection
            TourneySelection
            DiffEvolutionSelection
        )
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#    set(x "D:/LLVM-11.01/lib/clang/11.0.1/lib/windows")
#    target_compile_options(${target} PRIVATE -fsanitize=address -fno-omit-frame-pointer)
#    target_link_directories(${target} PRIVATE "${x}")
#    target_link_libraries(${target} PRIVATE clang_rt.asan_dynamic-x86_64 clang_rt.asan_dynamic_runtime_thunk-x86_64)
#    target_link_options(${target} PRIVATE /wholearchive:clang_rt.asan_dynamic_runtime_thunk-x86_64.lib)


#set(target SRESC)
#add_library(${target} SHARED CSRES.cpp CSRES.h)
#target_link_libraries(${target} PUBLIC SRES)


install(
        TARGETS opt
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)









