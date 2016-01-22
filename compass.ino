#include <U8glib.h>
#include <COMPASS64X13.h>
#include <Wire.h>
#include <LSM303.h>

LSM303 compass;

U8GLIB_SSD1306_64X48 u8g(14, 11, 10, 8, 9);   //MicroView OLED
 

int headingInt = 0;          //Compass heading as integer
const unsigned char* compassString[]={            //Compass Bitmaps in degrees
compass1_bits, compass2_bits, compass3_bits, compass4_bits, compass5_bits, compass6_bits, compass7_bits, compass8_bits, compass9_bits, compass10_bits,
compass11_bits, compass12_bits, compass13_bits, compass14_bits, compass15_bits, compass16_bits, compass17_bits, compass18_bits, compass19_bits, compass20_bits,
compass21_bits, compass22_bits, compass23_bits, compass24_bits, compass25_bits, compass26_bits, compass27_bits, compass28_bits, compass29_bits, compass30_bits,
compass31_bits, compass32_bits, compass33_bits, compass34_bits, compass35_bits, compass36_bits, compass37_bits, compass38_bits, compass39_bits, compass40_bits,
compass41_bits, compass42_bits, compass43_bits, compass44_bits, compass45_bits, compass46_bits, compass47_bits, compass48_bits, compass49_bits, compass50_bits,
compass51_bits, compass52_bits, compass53_bits, compass54_bits, compass55_bits, compass56_bits, compass57_bits, compass58_bits, compass59_bits, compass60_bits,
compass61_bits, compass62_bits, compass63_bits, compass64_bits, compass65_bits, compass66_bits, compass67_bits, compass68_bits, compass69_bits, compass70_bits,
compass71_bits, compass72_bits, compass73_bits, compass74_bits, compass75_bits, compass76_bits, compass77_bits, compass78_bits, compass79_bits, compass80_bits,
compass81_bits, compass82_bits, compass83_bits, compass84_bits, compass85_bits, compass86_bits, compass87_bits, compass88_bits, compass89_bits, compass90_bits,
compass91_bits, compass92_bits, compass93_bits, compass94_bits, compass95_bits, compass96_bits, compass97_bits, compass98_bits, compass99_bits, compass100_bits,

compass101_bits, compass102_bits, compass103_bits, compass104_bits, compass105_bits, compass106_bits, compass107_bits, compass108_bits, compass109_bits, compass110_bits,
compass111_bits, compass112_bits, compass113_bits, compass114_bits, compass115_bits, compass116_bits, compass117_bits, compass118_bits, compass119_bits, compass120_bits,
compass121_bits, compass122_bits, compass123_bits, compass124_bits, compass125_bits, compass126_bits, compass127_bits, compass128_bits, compass129_bits, compass130_bits,
compass131_bits, compass132_bits, compass133_bits, compass134_bits, compass135_bits, compass136_bits, compass137_bits, compass138_bits, compass139_bits, compass140_bits,
compass141_bits, compass142_bits, compass143_bits, compass144_bits, compass145_bits, compass146_bits, compass147_bits, compass148_bits, compass149_bits, compass150_bits,
compass151_bits, compass152_bits, compass153_bits, compass154_bits, compass155_bits, compass156_bits, compass157_bits, compass158_bits, compass159_bits, compass160_bits,
compass161_bits, compass162_bits, compass163_bits, compass164_bits, compass165_bits, compass166_bits, compass167_bits, compass168_bits, compass169_bits, compass170_bits,
compass171_bits, compass172_bits, compass173_bits, compass174_bits, compass175_bits, compass176_bits, compass177_bits, compass178_bits, compass179_bits, compass180_bits,
compass181_bits, compass182_bits, compass183_bits, compass184_bits, compass185_bits, compass186_bits, compass187_bits, compass188_bits, compass189_bits, compass190_bits,
compass191_bits, compass192_bits, compass193_bits, compass194_bits, compass195_bits, compass196_bits, compass197_bits, compass198_bits, compass199_bits, compass200_bits,

compass201_bits, compass202_bits, compass203_bits, compass204_bits, compass205_bits, compass206_bits, compass207_bits, compass208_bits, compass209_bits, compass210_bits,
compass211_bits, compass212_bits, compass213_bits, compass214_bits, compass215_bits, compass216_bits, compass217_bits, compass218_bits, compass219_bits, compass220_bits,
compass221_bits, compass222_bits, compass223_bits, compass224_bits, compass225_bits, compass226_bits, compass227_bits, compass228_bits, compass229_bits, compass230_bits,
compass231_bits, compass232_bits, compass233_bits, compass234_bits, compass235_bits, compass236_bits, compass237_bits, compass238_bits, compass239_bits, compass240_bits,
compass241_bits, compass242_bits, compass243_bits, compass244_bits, compass245_bits, compass246_bits, compass247_bits, compass248_bits, compass249_bits, compass250_bits,
compass251_bits, compass252_bits, compass253_bits, compass254_bits, compass255_bits, compass256_bits, compass257_bits, compass258_bits, compass259_bits, compass260_bits,
compass261_bits, compass262_bits, compass263_bits, compass264_bits, compass265_bits, compass266_bits, compass267_bits, compass268_bits, compass269_bits, compass270_bits,
compass271_bits, compass272_bits, compass273_bits, compass274_bits, compass275_bits, compass276_bits, compass277_bits, compass278_bits, compass279_bits, compass280_bits,
compass281_bits, compass282_bits, compass283_bits, compass284_bits, compass285_bits, compass286_bits, compass287_bits, compass288_bits, compass289_bits, compass290_bits,
compass291_bits, compass292_bits, compass293_bits, compass294_bits, compass295_bits, compass296_bits, compass297_bits, compass298_bits, compass299_bits, compass300_bits,

compass301_bits, compass302_bits, compass303_bits, compass304_bits, compass305_bits, compass306_bits, compass307_bits, compass308_bits, compass309_bits, compass310_bits,
compass311_bits, compass312_bits, compass313_bits, compass314_bits, compass315_bits, compass316_bits, compass317_bits, compass318_bits, compass319_bits, compass320_bits,
compass321_bits, compass322_bits, compass323_bits, compass324_bits, compass325_bits, compass326_bits, compass327_bits, compass328_bits, compass329_bits, compass330_bits,
compass331_bits, compass332_bits, compass333_bits, compass334_bits, compass335_bits, compass336_bits, compass337_bits, compass338_bits, compass339_bits, compass340_bits,
compass341_bits, compass342_bits, compass343_bits, compass344_bits, compass345_bits, compass346_bits, compass347_bits, compass348_bits, compass349_bits, compass350_bits,
compass351_bits, compass352_bits, compass353_bits, compass354_bits, compass355_bits, compass356_bits, compass357_bits, compass358_bits, compass359_bits, compass360_bits,
};

void setup(void) 
{
  Serial.begin(9600);
  Wire.begin();
  compass.init();
  compass.enableDefault();
    /*
  Calibration values; the default values of +/-32767 for each axis
  lead to an assumed magnetometer bias of 0. Use the Calibrate example
  program to determine appropriate values for your particular unit.
  */
  compass.m_min = (LSM303::vector<int16_t>){-32767, -32767, -32767};
  compass.m_max = (LSM303::vector<int16_t>){+32767, +32767, +32767};
  
} 

void draw(void){
  u8g.setFont(u8g_font_6x13);     //draw compass heading
  if (headingInt <= 9 ){          //center number on screen
    u8g.setPrintPos( 30, 24);
    u8g.print(headingInt);
    u8g.setPrintPos( 36, 24);
    u8g.print((char)176);       //Degree symbol
   }
     else if (headingInt >= 10 && headingInt <= 99){ //center
       u8g.setPrintPos( 27, 24);
       u8g.print(headingInt);
       u8g.print((char)176);
     }
       else if (headingInt >= 100){              //center
         u8g.setPrintPos( 23, 24);
         u8g.print(headingInt);
         u8g.print((char)176);
       }
  u8g.drawXBMP( 0, 0, 64, 13, compassString[headingInt]); // Draw bitmap based on compass heading
}
 
void loop(void) 
{
  compass.read();
  
  float heading = compass.heading((LSM303::vector<int>){1, 0, 0}); //Vector reference for noth heading {X, Y, Z}
  int headingInt = heading;
  if (headingInt < 1) {
    headingInt = 360 + headingInt;
  }
  
  Serial.println(heading);
  Serial.println(headingInt);
  
  
    // picture loop
  u8g.firstPage();  
  do {
    //draw();
  } while( u8g.nextPage() );
  
  
  delay(300);
}
