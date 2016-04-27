#!/bin/bash

#
# indent.sh
#
# Copyright (C) 2016 frnmst (Franco Masotti) <franco.masotti@live.com>
#                                            <franco.masotti@student.unife.it>
#
# This file is part of salibc.
#
# salibc is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# salibc is distributed in the hope that it will be
# useful,but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with salibc.  If not, see <http://www.gnu.org/licenses/>.
#

indentOptions="$1"
splintOptions="$2"
paths="$3"

# Set indent backup suffix.
export SIMPLE_BACKUP_SUFFIX=".indent.bak"

# Check if indent and splint executable exists.
which indent splint 1>/dev/null 2>/dev/null

if [ $? -eq 0 ]; then
    for file in $paths; do
        file="${file:0:(-2)}.c"
        splint $splintOptions "$file"
        indent $indentOptions "$file"
        # Remove indent backup files.
        rm "${file}${SIMPLE_BACKUP_SUFFIX}"

        # Get header path (.h files).
        file="${file:0:(-2)}.h"
        [ -f "$file" ] \
&& { indent $indentOptions "$file"; rm "${file}${SIMPLE_BACKUP_SUFFIX}"; }
    done;
fi

