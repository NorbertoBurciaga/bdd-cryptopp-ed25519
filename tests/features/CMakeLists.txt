# Define add_cucumber_executable function. It adds a prefix flag to each cpp in order to merge them into one executable 
function(add_cucumber_executable)
	add_executable(CucumberStepsServer ${ARGV})
	target_link_libraries(CucumberStepsServer cryptopp cucumber-cpp GTest::GTest ${Boost_LIBRARIES})
	foreach(_arg ${ARGN})
		get_filename_component(OBJECT_PREFIX ${_arg} NAME_WE)
		set_source_files_properties(${_arg} PROPERTIES COMPILE_FLAGS "-DCUKE_OBJECT_PREFIX=${OBJECT_PREFIX}")
	endforeach(_arg)
endfunction()

# add cpp files to the CucumberStepsServer executable
add_cucumber_executable(
	step_definitions/KeySteps
	step_definitions/SignatureSteps
)
