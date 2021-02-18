import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class Pam {
private BufferedImage s;
private String putanja;
private long velicina;
String rgb="",maxval="";
public Pam() {}
public Pam(BufferedImage s1) {
	s=s1;
}
public BufferedImage dohvatiSloj() {
	return s;
}
public String dohvatiPutanju() {
	return putanja;
}
	 public Sloj ucitaj(String putanja){
		 FileInputStream ulaz=null ;
		 try {
			 ulaz = new FileInputStream(putanja);
		
			
			// velicina = new File(putanja).length();
			byte bajtovi ;
			 System.out.print("aaaaaa");
            String visina="",sirina="",dubina="";//,rgb="",maxval="";
				//ulaz.read(bajtovi);
				bajtovi=(byte)ulaz.read();
			
				int cur=0;
				while(bajtovi!=0x20)	bajtovi=(byte)ulaz.read();
				bajtovi=(byte)ulaz.read();
				while (bajtovi!= 0x0a ) {
					sirina+=(bajtovi-48);
					bajtovi=(byte)ulaz.read();
				}
				
				
				 System.out.print("aaaaaa"+sirina);
				 while(bajtovi!=0x20)	bajtovi=(byte)ulaz.read();
					bajtovi=(byte)ulaz.read();
				while (bajtovi!= 0x0a ) {
					visina+=(bajtovi-48);
					bajtovi=(byte)ulaz.read();
				}
				 while(bajtovi!=0x20)	bajtovi=(byte)ulaz.read();
					bajtovi=(byte)ulaz.read();
				
				 System.out.print("aaaaaa"+visina);
				cur+=7;
				while (bajtovi!= 0x0a ) {
					dubina+=(bajtovi-48);
					bajtovi=(byte)ulaz.read();
				}
				 while(bajtovi!=0x20)	bajtovi=(byte)ulaz.read();
				 
					bajtovi=(byte)ulaz.read();
				 System.out.print("aaaaaa"+dubina);
				cur+=8;
				while (bajtovi!= 0x0a ) {
					maxval+=(bajtovi-48);
					bajtovi=(byte)ulaz.read();
				}
				 while(bajtovi!=0x20)	bajtovi=(byte)ulaz.read();
					bajtovi=(byte)ulaz.read();
				 System.out.print("aaaaaa"+maxval);
				cur+=10;
				while (bajtovi!= 0x0a ) {
					rgb+=bajtovi;
					bajtovi=(byte)ulaz.read();
				}
				 System.out.print("aaaaaa"+rgb);
				
				 while(bajtovi!=0x0a)	bajtovi=(byte)ulaz.read();
					//bajtovi=(byte)ulaz.read();
			
			if(Integer.parseInt(maxval)==255 && rgb.equals("827166")){
				 s = new BufferedImage(Integer.parseInt(sirina) , Integer.parseInt(visina), BufferedImage.TYPE_INT_RGB);
				for(int i=0;i<Integer.parseInt(visina);i++)
					for(int j=0;j<Integer.parseInt(sirina);j++) {
						
						bajtovi=(byte)ulaz.read();
						int r=(int)(bajtovi<<16);
						bajtovi=(byte)ulaz.read();
						int g=(int)(bajtovi<<8);
						bajtovi=(byte)ulaz.read();
						int b=(int)(bajtovi);
						int rgbcol=r+g+b;
						s.setRGB(i, j,rgbcol);
						
						
					}
				
			}
			else 	if(Integer.parseInt(maxval)==255 && rgb.equals("RGB_ALPHA")){
				 s = new BufferedImage(Integer.parseInt(sirina) , Integer.parseInt(visina), BufferedImage.TYPE_INT_ARGB);
				for(int i=0;i<Integer.parseInt(visina);i++)
					for(int j=0;j<Integer.parseInt(sirina);j++) {
						bajtovi=(byte)ulaz.read();
						int r=(int)(bajtovi<<16);
						bajtovi=(byte)ulaz.read();
						int g=(int)(bajtovi<<8);
						bajtovi=(byte)ulaz.read();
						int b=(int)(bajtovi);
						bajtovi=(byte)ulaz.read();
						int a=(int)(bajtovi<<24);
						int rgba=r+g+b+a;
						s.setRGB(i, j,rgba);
						
						
					}
				
			}
			else {
				throw new Exception();
				
			}
				
			
				
		 }
			catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		 catch(Exception e) {
			 System.out.print("Los ssformat slike");
			 System.out.print(Integer.parseInt(maxval));
				System.out.print(Integer.parseInt(rgb));
		 }
		
			return new Sloj(s);
	}
	public void sacuvaj(String putanja,BufferedImage bi) {
		try {
			FileOutputStream izlaz = new FileOutputStream(putanja);
			String heder = "P7"+'\n'+"WIDTH "+bi.getWidth()+'\n'+"HEIGHT "+bi.getHeight()+'\n'+"DEPTH 3"+'\n'+"MAXVAL 255"+'\n'+"TUPLTYPE RGB"+'\n'+"ENDHDR"+'\n';
			
					izlaz.write(heder.getBytes());
								
				
					byte bajt;
				for (int i = 0 ; i <  bi.getHeight();i++) {
					for (int j = 0 ; j < bi.getWidth();j++) {
						int argb = bi.getRGB(j, i);
						
						bajt = (byte)((argb & 0x00ff0000) >> 16);
						izlaz.write(argb);
						bajt = (byte)((argb & 0x0000ff00) >> 8);
						izlaz.write(argb);
						bajt = (byte)((argb & 0x000000ff) );
						izlaz.write(argb);
					//	bajt = (byte)((argb & 0xff000000) >> 24);
					}
				}
				
				izlaz.close();
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
  public static void main(String [] args) {
	  Pam p=new Pam();
	  p.ucitaj("C:\\Users\\PC\\Desktop\\slika.pam");
	  BufferedImage bi=new Sloj("C:\\Users\\PC\\Desktop\\slika.bmp").dohvatiSloj();
	  p.sacuvaj("C:\\Users\\PC\\Desktop\\slika34.pam",bi);
  }
}
