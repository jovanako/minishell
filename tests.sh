test_output_contains() {
    local expected="$1"
    local input_command="$2"

    # Run ./minishell with heredoc input and capture output
    local output
    output=$(./minishell <<EOF
$input_command
EOF
)

	# Define ANSI color codes
    GREEN='\033[0;32m'
    RED='\033[0;31m'
    NC='\033[0m' # No Color / reset

    # Check if the expected string is in the output
    if grep -q "$expected" <<< "$output"; then
        echo -e "${GREEN}PASS:${NC} '$expected' found in output of '$input_command'"
    else
        echo -e "${RED}FAIL:${NC} '$expected' not found in output of '$input_command'"
        echo "Output was:"
        echo "$output"
    fi
}

test_output_contains "hello" "echo hello"
test_output_contains "bla" "echo bla | grep a"
test_output_contains "oranges" \
'echo hello > infile
echo world >> infile
echo apples >> infile
echo oranges >> infile
cat infile | sort | grep g'
test_output_contains "hello" \
'echo hello > infile
cat infile'
test_output_contains "$USER" 'echo $USER'
test_output_contains "USER=$USER" "env | grep USER="
test_output_contains "XXX=$XXX" "XXX=xxx env | grep XXX"
test_output_contains "/home/jovana/Desktop/42Berlin/minishell" "pwd"
test_output_contains "/home/jovana/Desktop/42Berlin" \
'cd ..
pwd'