
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.HashMap;

public class Slika {
private Slika() {
	sirina=visina=0;
}
static private  Slika instancaSlike=null;
private int sirina,visina;
public int dohvatiSirinu() {return sirina;}
public int dohvatiVisinu() {return visina;}
    public static Slika dohvatiSliku() {
    	if(instancaSlike==null) {
    		instancaSlike=new Slika();
    	}
    	
    	return instancaSlike;
    }
    HashMap<String, Selekcija> selekcije = new HashMap<String, Selekcija>();
     ArrayList<Sloj> slojevi =new ArrayList<>();
    public void dodajSloj(Sloj s) {
    	
    	slojevi.add(s);
    
    	
    		 sirina=sirina>s.dohvatiSirinu()?sirina:s.dohvatiSirinu();
    		 visina=visina>s.dohvatiVisinu()?visina:s.dohvatiVisinu();
    	
    	//s.postaviIndeks(slojevi.size());
    }
    public void dodajSloj(String s) {
    	
    if(s.endsWith(".bmp")) {
    	//System.out.print(2);
    	Sloj slo=new Sloj(s);
    //	System.out.print(slo.dohvatiSirinu());
    //	System.out.print(slo.dohvatiVisinu());
    	dodajSloj( slo);
    	
    }
    else if(s.endsWith(".pam")) {
    	dodajSloj((new Pam()).ucitaj(s));
    }
    else if(s.endsWith(".xml")) {
    	Xml.Ucitaj(s);
    }
    
    
    }
    public void obrisiSloj(int a) {
    	slojevi.remove(a);
    }
    
    public int dohvatiBrojSlojeva() {
    	return slojevi.size();
    }
    public Sloj  dohvatiCitavuSliku() {
    
    	BufferedImage bi=new BufferedImage(sirina, visina, BufferedImage.TYPE_INT_RGB);
    	for(int i=0;i<visina;i++)
    		for(int j=0;j<sirina;j++) {
    			int rgb=0;
    			double d=100;
    			int rgba=0;
    			for(int k=0;k<slojevi.size();k++) {
    				
    				
    				if(slojevi.get(k).dohvatiAktivan() && (i<slojevi.get(k).dohvatiVisinu() && j<slojevi.get(k).dohvatiSirinu())) {
    					 rgba=slojevi.get(k).dohvatiSloj().getRGB(j, i);
    			
    				    int r=(rgba & 0x00ff0000)>>16;
    				//if(r!=255)System.out.print(rgba);
    		        	int g=(rgba & 0x0000ff00)>>8;
    	                int b=(rgba & 0x000000ff);
    	                int a=(rgba & 0xff000000)>>24;
    	               
    					r=(int)((double)r*(double)(d*slojevi.get(k).dohvatiProzirnost()/10000));
    					
    					g=(int)((double)g*(double)(d*slojevi.get(k).dohvatiProzirnost()/10000));
    				
    					b=(int)((double)b*(double)(d*slojevi.get(k).dohvatiProzirnost()/10000));
    					rgb+=((r<<16)+(g<<8)+b+(255<<24));
    					d-=(d*(slojevi.get(k).dohvatiProzirnost()))/100;
    					if(d<=0)break;
    				}
    				
    				
    			}
    			if(d>0)rgb+=((int)((d*255)/100))<<24;
    			if(d>0)rgb+=((int)((d*255)/100))<<16;
    			if(d>0)rgb+=((int)((d*255)/100))<<8;
    			if(d>0)rgb+=((int)((d*255)/100));
    			bi.setRGB(j, i, rgb);
    		}
    	
    	return new Sloj(bi);
    }
    public Sloj dohvatiSloj(int i) {
    	if(i>=0 && i<slojevi.size())
    	return slojevi.get(i);
    	
    	return null;
    }
    
	}

