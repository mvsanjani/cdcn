import java.util.Scanner;

public class CRC {

    // CRC division using XOR
    static void crcDivision(String data, String generator, StringBuilder remainder) {

        int dataLen = data.length();
        int genLen = generator.length();

        char[] temp = data.toCharArray();

        for (int i = 0; i <= dataLen - genLen; i++) {

            if (temp[i] == '1') {

                for (int j = 0; j < genLen; j++) {

                    if (temp[i + j] == generator.charAt(j))
                        temp[i + j] = '0';
                    else
                        temp[i + j] = '1';
                }
            }
        }

        // Last 12 bits are the CRC remainder
        remainder.append(temp, dataLen - genLen + 1, genLen - 1);
    }


    // Convert word into 8-bit ASCII binary
    static String wordToBinary(String word) {

        StringBuilder binary = new StringBuilder();

        for (int i = 0; i < word.length(); i++) {

            int ch = word.charAt(i);

            for (int j = 7; j >= 0; j--) {

                if ((ch & (1 << j)) != 0)
                    binary.append("1");
                else
                    binary.append("0");
            }
        }

        return binary.toString();
    }


    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        String word;

        // CRC-12 generator:
        // x^12 + x^11 + x^3 + x^2 + x + 1
        String generator = "1100000001111";

        String data;
        String paddedData;
        String remainder;
        String transmitted;


        System.out.print("Enter a word: ");
        word = sc.next();


        // Convert word to binary
        data = wordToBinary(word);

        System.out.println("\nData in binary    : " + data);
        System.out.println("CRC-12 Generator  : " + generator);


        // Append 12 zeros
        paddedData = data;

        for (int i = 0; i < 12; i++)
            paddedData += "0";


        // Calculate CRC
        StringBuilder rem = new StringBuilder();

        crcDivision(paddedData, generator, rem);

        remainder = rem.toString();

        System.out.println("CRC-12 Remainder  : " + remainder);


        // Create transmitted data
        transmitted = data + remainder;

        System.out.println("Transmitted Data  : " + transmitted);


        sc.close();
    }
}