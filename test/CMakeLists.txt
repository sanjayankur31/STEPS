set(inc_dirs "${CMAKE_SOURCE_DIR}/src")
set(libs libsteps gtest_main gtest)

if(LAPACK_FOUND)
  list(APPEND libs ${LAPACK_LIBRARIES})
endif()

if(MPI_FOUND)
  list(APPEND libs ${MPI_CXX_LIBRARIES})
  list(APPEND inc_dirs ${MPI_CXX_INCLUDE_PATH})
  if(PETSC_FOUND)
    list(APPEND libs ${PETSC_LIBRARIES})
    list(APPEND inc_dirs ${PETSC_INCLUDE_DIRS})
  endif()
endif()

include_directories(${inc_dirs})

add_subdirectory(unit)
add_subdirectory(validation)
