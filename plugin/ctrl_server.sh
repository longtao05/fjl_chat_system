#!/bin/bash


ROOT=$(pwd)
CONF=${ROOT}/conf/server.conf
BIN=${ROOT}/chat_server
LOG=${ROOT}/log/server.log

server_pid=""
proc=$(basename $0)  
function usage(){
	printf "%s\033[31m%s\033[0m\n" "Usage :" "${proc} [start(-s) | stop(-o) | restart(-r) | status(-u)] "
}

function print_log()
{
	local msg=$1
	local level=$2
	local curr_time=$(date +%Y_%m_%d:%H:%M:%S)
	echo "[${curr_time}] [${msg}] [${level}]" >> ${LOG}
}


function server_status(){
	
	local name=$(basename ${BIN})
	#获取name 进程号 success return pid else no return 
	local stat=$(pidof ${name})
	if [ -z "${stat}" ];then
		return 1
	fi
	server_pid=${stat}
	return 0
}

function service_start(){
	if server_status; then
		echo "server is already running..."
		print_log "server is already running" "FATAL"
		return
	else
		local server_path=$(dirname ${BIN})
		local server_name=$(basename ${BIN})
		#获取port端口号
		local server_port=$(grep -E '^PORT :' ${CONF}|awk -F':' '{print $2}' | tr -d ' ')
		#将路径压人目录栈
		pushd ${server_path}
			./${server_name} ${server_port} 1>/dev/null 2>/dev/null
		#将目录弹出目录栈
		popd
	fi

	if server_status; then
		echo "start success"
		print_log "start server success" "NOTICE"
	else
		echo "start failed"
		print_log "start server failed" "FATAL"
	fi
}

function service_stop(){
	if server_status; then
		kill -9 ${server_pid}
		echo "stop success"
		print_log "server is running, stop success" "NOTICE"
	else
		echo "server is not exist, does't need stop"
		print_log "server is not running, does't need stop" "NOTICE"
	fi
}

function service_restart(){
	service_stop
	service_start
}

function service_status(){
	if server_status; then
		echo "server is running now..."
		print_log "server is running..." "NOTICE"
	else
		echo "server is not running now..."
		print_log "server is not running..." "NOTICE"
	fi
}


####################################################
if [ $# -ne 1 ];then
	usage
	exit 1
fi



case $1 in
	"-s"|"start" )
		service_start
	;;
	"-o"|"stop" )
		service_stop
	;;
	"-r"|"restart" )
		service_restart
	;;
	"-u"|"status" )
		service_status
	;;
	* )
		usage
		exit 1
	;;
esac
exit 0
