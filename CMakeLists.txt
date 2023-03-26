if (NOT TARGET battery_check)
    add_library(battery_check INTERFACE)

    target_sources(battery_check INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/battery-check.c
    )

    target_include_directories(battery_check INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}
    )

    target_link_libraries(battery_check INTERFACE
        pico_stdlib
        hardware_adc
    )
endif()