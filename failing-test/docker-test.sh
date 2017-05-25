#!/bin/bash
cd $(dirname $0)/..

script_name="tests.sh"

docker_image="not_working"

project_mount_folder="/vips-test"

cmdline="docker run -t -i -v $PWD/failing-test:$project_mount_folder -w $project_mount_folder \
	--rm \
	$docker_image \
	./$script_name $@"

echo "DEBUG: executing $cmdline"
eval $cmdline

