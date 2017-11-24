file(REMOVE_RECURSE
  "src/hlsyn.pdb"
  "src/hlsyn"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/hlsyn.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
