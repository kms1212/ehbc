#!/bin/bash

set -euo pipefail
BASEDIR=$(cd "$(dirname "$BASH_SOURCE")" && pwd)

echo "Pattern Checker Script"
echo "BASEDIR=$BASEDIR"

echo "Running \"which ag\"... $(which ag)"

ag --stats "$(cat "agpatterns.txt")" --ignore "before_you_commit.sh" --ignore "agpatterns.txt" $BASEDIR
