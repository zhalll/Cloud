#include "CloudEulerGen.h"
#include "WriteVTI.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

namespace py = pybind11;


PYBIND11_MODULE(Cloud_Gen_Based_Euler, m) {
	py::class_<CloudEulerGen>(m, "CloudEulerGen")
		.def(py::init<const std::vector<int>&, const float>())
		.def("CloudGenFrameRun", &CloudEulerGen::CloudGenFrameRun)
		.def("CloudGenFinalRun", &CloudEulerGen::CloudGenFinalRun)
		.def("GetVaporDensity", 
			static_cast<const std::vector<float>& (CloudEulerGen::*)()>(&CloudEulerGen::GetVaporDensity), 
			py::return_value_policy::reference)
		.def("GetCloudDensity", 
			static_cast<const std::vector<float>& (CloudEulerGen::*)()>(&CloudEulerGen::GetCloudDensity), 
			py::return_value_policy::reference);

	m.def("WriteVTI", &WriteVTI);
}
