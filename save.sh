
setting_file="bank_setting.txt"

if [ $# -ne 2 ]
then
    while read line
    do
#	echo ${line}
	name=`echo ${line} | cut -d " " -f1`
	value=`echo ${line} | cut -d " " -f2`

	if [ "${name}" = "year" ];then
	    year=${value}
	elif [ "${name}" = "month" ];then
	    month=${value}
	fi
    done < ${setting_file}

    if [ "${year}" != "" -a "${month}" != "" ];then
	ans=no_answer
	while [ "${ans}" != "y" -a "${ans}" != "n" ]
	do
	    echo "year=${year} month=${month}   OK? [y/n]"
	    read ans
	done
	if [ "${ans}" = "n" ];then
	    echo "$0 [year] [month]"
	    exit
	fi
    else
	exit
    fi
else
    year=$1
    month=$2
fi

banknames="sapica suica 三井住友銀行 大学生協 小銭貯金 財布 郵便局"
outdir="${HOME}/Dropbox/other/housekeeping/rails"
filename="${year}.${month}.html"

tmp="tmp.html"

for bankname in ${banknames}
do
    echo ${bankname}

    url="http://localhost:3000/banks?bankname=${bankname}&year=${year}&month=${month}"

    wget -O ${tmp} ${url}
    # convert to shift-jis
    nkf -s ${tmp} > "${outdir}/${bankname}/${filename}"

    url="http://localhost:3000/banks?bankname=${bankname}"
    wget -O ${tmp} ${url}
    # convert to shift-jis
    nkf -s ${tmp} > "${outdir}/total/${bankname}.html"
done

url="http://localhost:3000/banks"
wget -O ${tmp} ${url}
nkf -s ${tmp} > "${outdir}/total/all.html"

url="http://localhost:3000/banks/0/newest.html"
wget -O ${tmp} ${url}
nkf -s ${tmp} > "${outdir}/newest.html"

rm ${tmp}