# Copyright 2016-2021 L. Pickering, P Stowell, R. Terri, C. Wilkinson, C. Wret

################################################################################
#    This file is part of NUISANCE.
#
#    NUISANCE is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    NUISANCE is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with NUISANCE.  If not, see <http://www.gnu.org/licenses/>.
################################################################################

set(Statistical_Impl_Files
  StatUtils.cxx
)

set(Statistical_Hdr_Files
  StatUtils.h
)

add_library(Statistical SHARED ${Statistical_Impl_Files})
target_link_libraries(Statistical CoreIncludes ROOT::ROOT)
set_target_properties(Statistical PROPERTIES PUBLIC_HEADER "${Statistical_Hdr_Files}")

install(TARGETS Statistical
    EXPORT nuisance-targets
    LIBRARY DESTINATION lib/
    PUBLIC_HEADER DESTINATION include)

add_library(NUIS::Statistical ALIAS Statistical)