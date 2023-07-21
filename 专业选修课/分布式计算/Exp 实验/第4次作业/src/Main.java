import wsproxy.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;

public class Main {

    public static void main(String[] args) throws IOException {
        EnglishChinese englishChinese = new EnglishChinese();
        EnglishChineseSoap englishChineseSoap =  englishChinese.getEnglishChineseSoap();
        ArrayOfString result;
        List<String> rs;



        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            try{
                System.out.print("���������ѯ�ĵ��ʣ�");
                String word = bufferedReader.readLine();
                result = englishChineseSoap.translatorString(word);
                rs = result.getString();

                System.out.println("-----��������----");
                for (String s: rs){
                    System.out.println(s);
                }
                System.out.println("-----����ʻ�----");
                result = englishChineseSoap.translatorReferString(word);
                rs = result.getString();
                for (String s: rs){
                    System.out.println(s);
                }

                System.out.println("-----�ο�����----");
                result = englishChineseSoap.translatorSentenceString(word);
                rs = result.getString();
                for (String s: rs){
                    System.out.println(s);
                }
                System.out.print("\n\n");

            }catch (Exception e){
                System.out.println("��ѯ������������");
            }
        }

    }

}