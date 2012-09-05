set (ROUBO_HEADERS Table.h
                   Row.h
                   Cell.h
                   Column.h
                   Common.h
                   FileHandler.h)

set (ROUBO_SOURCE Roubo.cpp
                  Cell.cpp
                  Row.cpp
                  Column.cpp
                  Table.cpp
                  FileHandler.cpp)

source_group (Headers FILES ${ROUBO_HEADERS})
add_executable(Roubo ${ROUBO_SOURCE} ${ROUBO_HEADERS})
