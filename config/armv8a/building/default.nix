/*
 * File: default.nix
 * Project: timesecbench
 * Created Date: Thursday November 5th 2020
 * Author: Ronan (ronan.lashermes@inria.fr)
 * -----
 * Last Modified: Tuesday, 4th May 2021 1:58:37 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

with import <nixpkgs> {
  crossSystem = {
    config = "aarch64-unknown-linux-gnu";
  };
};

mkShell {
  buildInputs = [ zlib ]; # your dependencies here
}