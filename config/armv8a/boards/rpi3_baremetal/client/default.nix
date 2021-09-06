/*
 * File: default.nix
 * Project: client
 * Created Date: Friday August 27th 2021
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Monday, 6th September 2021 10:02:23 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2021 INRIA
 */
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
    python3Packages.pyserial
    python3Packages.numpy
    python3Packages.termcolor
    python3Packages.matplotlib
    bash
  ];
}
