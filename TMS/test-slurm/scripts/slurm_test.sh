#!/bin/sh
# SBATCH -N4
#SBATCH -J myFristJob
#SBATCH -o myJob-%J.out
#SBATCH -e myJob-%J.err
#SBATCH -t 01:02:20
#SBATCH -p firstPart
srun hostname
sleep 120
echo "Hello word!...."
echo "The id of the submitted jobs is: "$SLURM_JOB_ID 
echo "Your job submit directory is: "$SLURM_SUBMIT_DIR
echo "The total number in your job's resource allocation is: "$SLURM_JOB_NUM_NODES
echo "The name of your job is: " $SLURM_JOB_NAME
echo "The list of nodes allocated to the job: " $SLURM_JOB_NODELIST
echo "The count of processors available to the job on this node: " $SLURM_JOB_CPUS_PER_NODE