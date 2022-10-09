<?php

// IHS <3

/**
 * 0 + 0 + 0 = 0
 * 0 + 0 + 1 = 1
 * 0 + 1 + 0 = 1
 * 0 + 1 + 1 = 0 (enable flag)
 * 
 * 1 + 1 + 1 = 1 (enable flag)
 */

$number1 = "101";
$number2 = "011";
$result  = "";
$size    = strlen($number1);
$flag    = false;

for ($a=($size-1); $a>=0; $a--) {
    $num1 = $number1[$a];
    $num2 = $number2[$a];
    $nret = '0';
    $cflag = $flag;

    if ($flag === false) {
        if ($num1 == '1' && $num2 == '1') {
            $nret = '0';
            $flag = true;
        }
        
        else if ($num1 == '0' && $num2 == '0')
            $nret = '0';
        else if ($num1 == '1' && $num2 == '0' || 
                 $num1 == '0' && $num2 == '1'  )
            $nret = '1';
    }

    else {
        if ($num1 == '1' && $num2 == '1')
            $nret = '1';

        else if ($num1 == '0' && $num2 == '0') {
            $nret = '1';
            $flag = false;
        }

        else if ($num1 == '1' && $num2 == '0' || 
                 $num1 == '0' && $num2 == '1'  ) {
            $nret = '0';
        }
    }

    $result .= $nret;

    echo (($cflag === true) ? '1' : '0') ." + ". 
            $num1 ." + ". $num2 ." = ". $nret .
            " (". ($flag ? 'true' : 'false') .")\n";
}

echo (($flag === true) ? '1' : '0') .
        " + 0 + 0 = ". (($flag === true) ? '1' : '0') ." (false)\n";

if ($flag === true)
    $result .= '1';

$result = strrev($result);

echo "\n";
echo "Decimal: ". bindec($number1) ." + ". bindec($number2) ." = ". bindec($result) ."\n";
echo "Binary.: ". $number1 ." + ". $number2 ." = ". $result ."\n";


