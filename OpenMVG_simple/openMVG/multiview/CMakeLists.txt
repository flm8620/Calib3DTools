ADD_LIBRARY(openMVG_multiview
projection.cpp
conditioning.cpp
conditioning.hpp
)
#Make multiview library integrate numeric library
TARGET_LINK_LIBRARIES(openMVG_multiview openMVG_numeric)
