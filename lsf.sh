#!/bin/bash
#BSUB -J lsf
#BSUB -o lsf_%J.out
#BSUB -e lsf_%J.err
#BSUB -q hpcintro
#BSUB -W 45 -n 24
#BSUB -R "select[model == XeonE5_2650v4]"
#BSUB -R "rusage[mem=512MB]"

parallel.sh
