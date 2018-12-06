using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DevInfoWrite
{
    class byteHexStringConv
    {
        public static string toHexString( byte[] bytes )
        {
            string hexString = string.Empty;

            if ( null != bytes )
            {
                StringBuilder strB = new StringBuilder();

                for ( int i = 0; i < bytes.Length; i ++)
                {
                    strB.Append(bytes[i].ToString("X2"));
                }

                hexString = strB.ToString();
            }

            return hexString;
        }

        public static byte[] getBytes( string hexString, out int discarded )
        {
            discarded = 0;
            string newString = "";
            char c;// remove all none A-F, 0-9, characters

            for ( int i = 0; i < hexString.Length; i++)
            {
                c = hexString[i];
                if ( IsHexDigit(c))
                    newString += c;
                else
                    discarded++;
            }// if odd number of characters, discard last character

            if (newString.Length % 2 != 0)
            {
                discarded++;                

                newString = newString.Substring(0, newString.Length - 1);
            }

            int byteLength = newString.Length / 2;
            byte[] bytes = new byte[byteLength];
            string hex;
            int j = 0;

            for (int i = 0; i<bytes.Length; i++){
                hex = new String(new Char[] {newString[j], newString[j + 1] });               
                bytes[i] = HexToByte(hex);
                j = j+2;           
            }
            return bytes;  
        }

        private static bool IsHexDigit( char c)
        {
            bool bRet = false;
            if ( ( c >= '0') && ( c <= '9' ))
            {
                bRet = true;
            }
            else if ((c >= 'A') && (c <= 'F'))
            {
                bRet = true;
            }
            else if ((c >= 'a') && (c <= 'f'))
            {
                bRet = true;
            }
            else
            {
                bRet = false;
            }

            return bRet;
        }

        private static byte HexToByte( string hexString )
        {
            byte []bHex = new byte[2];

            for ( int i = 0; i < 2; i++)
            {
                if (hexString[i] <= '9' && hexString[i] >= '0' )
                {
                    bHex[i] = (byte)(hexString[i] - '0');
                }
                else if (hexString[i] <= 'F' && hexString[i] >= 'A')
                {
                    bHex[i] = (byte)(hexString[i] - 'A' + 10);
                }
                else if (hexString[i] <= 'f' && hexString[i] >= 'a')
                {
                    bHex[i] = (byte)(hexString[i] - 'a' + 10);
                }
                else
                {
                    bHex[i] = 0;
                }
            }

            return (byte)((byte)(bHex[0] << 4) | bHex[1]);
        }
    }
}
