test_counter=1

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
    YELLOW='\033[0;33m'
    NC='\033[0m' # No Color / reset

    # Check if the expected string is in the output
    if grep -q "$expected" <<< "$output"; then
        echo -e "${GREEN}[$test_counter] PASS:${NC} '$expected' found in output of '$input_command'"

        # --- Only run Valgrind if functional test passed ---
        local valgrind_log="valgrind_${test_counter}.log"
        valgrind --leak-check=full --errors-for-leak-kinds=all \
				 --suppressions=readline.supp \
                 --error-exitcode=42 \
                 ./minishell <<EOF &> "$valgrind_log"
$input_command
EOF
        local valgrind_status=$?

        if [ $valgrind_status -eq 42 ]; then
            echo -e "${RED}[Valgrind FAIL]${NC} Memory errors detected. See $valgrind_log"
            exit 1   # 🔴 Stop script immediately
        else
            echo -e "${GREEN}[Valgrind PASS]${NC} No leaks/errors detected"
            rm "$valgrind_log" # cleanup if clean run
        fi
        # ---------------------------------------------------
    else
        echo -e "${RED}[$test_counter] FAIL:${NC} '$expected' not found in output of '$input_command'"
        echo "Command: $input_command"
        echo "Expected: $expected"
        echo "Output:"
        echo "$output"
    fi

    ((test_counter++))
}

#[1]
test_output_contains "hello" \
"echo hello"

#[2]
test_output_contains "nested 'quotes' are tricky" \
"echo \"nested 'quotes' are tricky\""

#[3]
test_output_contains "nested \"quotes\" are tricky too" \
"echo 'nested \"quotes\" are tricky too'"

#[4]
test_output_contains "hello world" \
"echo \"hello world\""

#[5]
test_output_contains "hello world" \
"echo 'hello world'"

#[6]
test_output_contains "invalid input" \
"echo \"unterminated"

#[7]
test_output_contains "bla{man$USER" \
"echo bla{man$USER"

#[8]
test_output_contains "$USER" \
"echo \"$USER\""

#[9]
test_output_contains '$USER' \
"echo '"'$USER'"'"

#[10]
test_output_contains "\n" \
"echo $UNSET_VAR"

#[11]
test_output_contains "VAR=abc$USER" \
"export VAR=abc$USER"

#[12]
test_output_contains "bla" \
"echo bla | grep a"

#[13]
test_output_contains "oranges" \
'echo hello > infile
echo world >> infile
echo apples >> infile
echo oranges >> infile
cat infile | sort | grep g'

#[14]
test_output_contains "hello" \
'echo hello > infile
cat infile'

#[15]
test_output_contains "$USER" \
'echo $USER'

#[16]
test_output_contains "USER=$USER" \
"env | grep USER="

#[17]
test_output_contains "XXX=$XXX" \
"XXX=xxx env | grep XXX"

#[18]
test_output_contains "/home/jovana/Desktop/42Berlin/minishell" "pwd"

#[19]
test_output_contains "/home/jovana/Desktop/42Berlin" \
'cd ..
pwd'

#[20]
test_output_contains "BLA=bla" \
'export BLA=bla
env | grep BLA'

#[21]
test_output_contains "BLA=a" \
'export BLA=bla
BLA=a
env | grep BLA'

#[22]
test_output_contains "VAR=bla bla" \
'export VAR="bla bla"
env | grep VAR'

#[23]
test_output_contains "minishell: something: No such file or directory" \
'< something cat'

#[24]
test_output_contains "minishell: /etc/shadow: Permission denied" \
'< /etc/shadow cat'

#[25]
test_output_contains "minishell: /etc/pam.conf: Permission denied" \
'echo bla > /etc/pam.conf'

#[26]
test_output_contains "minishell: /etc/pam.conf: Permission denied" \
'echo bla >> /etc/pam.conf'

#[27]
test_output_contains "minishell: ./outfile: Permission denied" \
'./outfile'

#[28]
test_output_contains "hello" \
'/usr/bin/cat infile'

#[29]
test_output_contains "minishell: cmd: command not found" \
'cmd'

#[30]
test_output_contains "minishell: /etc/pam.conf: Permission denied" \
'blablabla >> /etc/pam.conf'

#[31]
test_output_contains "minishell: /home: Is a directory" \
'echo bla > /home'

#[32]
test_output_contains "minishell: /home: Is a directory" \
'echo bla >> /home'

#[33]
test_output_contains "minishell: /home: Is a directory" \
'echo bla > /home'

#[34]
test_output_contains "minishell: cd: too many arguments" \
'cd bla bla'

#[35]
test_output_contains "minishell: cd: ffff: No such file or directory" \
'cd ffff'

#[36]
test_output_contains "minishell: syntax error near unexpected token \`|" \
'| ls'

#[37]
test_output_contains "minishell: syntax error near unexpected token \`newline" \
'<<'

#[38]
test_output_contains "minishell: syntax error near unexpected token \`newline" \
'echo hello >'

#[39]
test_output_contains "minishell: syntax error near unexpected token \`newline" \
'echo hello >>'

#[40]
test_output_contains "minishell: syntax error near unexpected token \`newline" \
'echo hello <'

#[41]
test_output_contains "/tmp" \
'cd /tmp
pwd'

#[42]
test_output_contains "$HOME" \
'cd
pwd'

#[43]
test_output_contains "$PWD" \
'pwd'

#[44]
test_output_contains "Makefile" \
'ls | grep Makefile'

#[45]
test_output_contains "hello" \
'echo hello | cat'

#[46]
test_output_contains "hello" \
'echo hello > infile
cat < infile'

#[47]
test_output_contains "1" \
'wc -w < infile'

#[48]
test_output_contains "hello" \
'< infile cat'

#[49]
test_output_contains "word" \
'echo word > infile
cat infile'

#[50]
test_output_contains "hello" \
'echo hello > infile
cat infile'

#[51]
test_output_contains "line2" \
'echo line1 >> infile
echo line2 >> infile
cat infile | grep 2'

#[52]
test_output_contains "hello" \
'echo hello > infile
cat < infile > outfile
cat outfile'

#[53]
test_output_contains "" \
'pwd'

# add exit tests