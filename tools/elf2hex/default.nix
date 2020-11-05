with import <nixpkgs> {};

let
     pkgs = import (builtins.fetchGit {
         # Descriptive name to make the store path easier to identify                
         name = "my-old-revision";                                                 
         url = "https://github.com/nixos/nixpkgs-channels/";                       
         ref = "refs/heads/nixos-20.03";                     
         rev = "1975b8687474764c157e6a220fdcad2c5dc348a1";                                           
     }) {};                                                                           

in

 # Make a new "derivation" that represents our shell
stdenv.mkDerivation {
  name = "apps_builder";

  # The packages in the `buildInputs` list will be added to the PATH in our shell
  buildInputs = with pkgs; [
    python3
    pythonPackages.click
    pythonPackages.pyelftools
    bash
  ];
}
