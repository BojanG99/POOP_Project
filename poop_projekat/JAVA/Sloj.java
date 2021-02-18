
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

import java.awt.image.BufferedImage;
public class Sloj  {

	private boolean aktivan=true,ucestvuje=true;
	private int sirina,visina;
	private int prozirnost,indeks;
	private BufferedImage sloj;
	public int dohvatiIndeks() {
		return indeks;
	}
	public void postaviIndeks(int i) {
		indeks=i;
	}
public Sloj(BufferedImage bi) {
	sloj=bi;
	visina=sloj.getHeight();
	sirina=sloj.getWidth();
  prozirnost=100;
}
	public Sloj(String ime) {
		 prozirnost=50;
		File slika=new File(ime);
		
		
		File upis=new File("C:\\Users\\PC\\Desktop\\bempesdds1sa.bmp");
		try {
			sloj=ImageIO.read(slika);
			visina=sloj.getHeight();
			sirina=sloj.getWidth();
			BufferedImage ia=new BufferedImage(sirina,visina,BufferedImage.TYPE_INT_RGB);
			for(int i=0;i<sirina;i++) {
				for(int j=0;j<visina;j++)
					ia.setRGB(i, j, sloj.getRGB(i, j));
			}
			ImageIO.write(ia, "bmp", upis);
			visina=sloj.getHeight();
			sirina=sloj.getWidth();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.out.print("ne postoji slika");
		}
	}
	public boolean dohvatiAktivan() {
		return aktivan;
	}
	public boolean dohvatiUcestvuje() {
		return ucestvuje;
	}
	public int dohvatiSirinu() {
	return sirina;
	}
	public int dohvatiVisinu() {
		return visina;
	}
	public int dohvatiProzirnost() {
		return prozirnost;
	}
	public BufferedImage dohvatiSloj() {
		return sloj;
	}
   public void postaviAktivan(boolean b) {aktivan=b;}
   public void postaviUcestvuje(boolean b) {ucestvuje=b;}
   public void postaviSirinu(int s) {sirina=s;}
   public void postaviVisinu(int s) {visina=s;}
   public void postaviProzirnost(int s) {prozirnost=s;}
   public void postaviSloj(BufferedImage bi) {sloj=bi;}
   public static void main (String args[]) {
   Sloj s=new Sloj("C:\\Users\\PC\\Desktop\\slika.bmp");
   System.out.print("alooo");
   }
   
}
   
