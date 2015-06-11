file(GLOB SOURCE_FILES "*.cpp")
add_library(ClickImage ${SOURCE_FILES})
target_link_libraries(ClickImage Qt5::Widgets)
