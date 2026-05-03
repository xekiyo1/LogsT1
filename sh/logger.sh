dateString=$(eval "date +\"log_%d%m%Y__%T.log\"")

file=./logs/$dateString
install -Dv /dev/null $file
./sh/cli.sh | tee $file