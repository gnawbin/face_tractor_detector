
add_executable(annotate_main annotate_main.cpp)
target_link_libraries(annotate_main ${OpenCV_LIBS} ft_base)
add_executable(visualize_annotations visualize_annotations.cpp)
target_link_libraries(visualize_annotations ${OpenCV_LIBS} ft_base)
add_executable(train_shape_model train_shape_model.cpp)
target_link_libraries(train_shape_model ${OpenCV_LIBS} ft_base)