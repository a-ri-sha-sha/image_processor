add_executable(
        image_processor
        image_processor.cpp
        filter.h tmatrix.h crop.cpp crop.h grayscale.cpp grayscale.h negative.cpp negative.h sharpening.cpp sharpening.h edge_detection.cpp edge_detection.h gaussian_blur.cpp gaussian_blur.h bitmap.cpp bitmap.h parser.h filter_description.h creators.h application.h pipeline.cpp pipeline.h application.cpp creators.cpp matrix_filter.cpp matrix_filter.h mirror.cpp mirror.h)
