file(GLOB SOURCE_FILES_CLICKIMAGE "*.cpp")
add_library(ClickImage ${SOURCE_FILES_CLICKIMAGE})
target_link_libraries(ClickImage Qt5::Widgets)
