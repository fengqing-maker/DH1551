#ifndef PEF_H_
#define PEF_H_

#define SECURE_PEFDATA_MAX_LENGTH	0x200

typedef struct
{
	unsigned int unFirstPos;
	unsigned int unItemSize;
	unsigned int unFirstChip;
}File_Info_S;

enum DATATYPE
{
	E_PEF,
	E_IFCP
};
class PEF
{
public:
	PEF();
	~PEF();

public:
	unsigned int PEFInit(char *pcChipID, int nLen);
	unsigned int GetFileName(char *cChipID, int nLen);
	unsigned int ParseAllData(unsigned char *pucChipID, unsigned char *pBuffer, unsigned int unLen);
	unsigned int ParseAllData(unsigned char *pucChipID, unsigned char *pBuffer, unsigned int unLen, DATATYPE eDataType);

	unsigned int ParsePEFData(unsigned char *pucChipID, unsigned int unChipID);
	unsigned int GetPEFData(unsigned char *pucBuffer, unsigned int unLen);

	unsigned int ParseIFCPData(unsigned char *pucChipID, unsigned int unChipID);
	unsigned int ConstructIFCPData(unsigned char *pucActMeg, unsigned int unLen);
	unsigned int GetIFCPData(unsigned char *pucBuffer, unsigned int unLen);

	unsigned int IRDCCA_Char2Hex(const unsigned char* pucSource, unsigned int nlength, unsigned char *pucDes);
	unsigned char ChartoNum(unsigned char ch);
	unsigned int LittleToBig(unsigned char *pBuffer, unsigned int unLen);
	unsigned int GetChipID(unsigned char *pBuffer, unsigned int unLen, unsigned int & unChipID);
	void ClearAllData(void);

protected:
	unsigned int GetFileInfo(char *pFileName, File_Info_S & stFileInfo);
	unsigned int GetSTHFileInfo();
	unsigned int GetFileItem(char *pBuffer, int nLen, char *pDest, int nDestLen, char *pStartData, char *pEndData);
	unsigned int GetCrc32(const unsigned char *pDataBuffer, unsigned int dataLength);
	unsigned int GetVersion(char *pacBuffer, int nLen);
	unsigned int GetIsTestImage(char *pacBuffer, int nLen);

private:
	unsigned char m_ucPEFHexData[SECURE_PEFDATA_MAX_LENGTH];
	unsigned int m_unPEFDataLen;
	unsigned char m_ucIFCPHexData[128 * 1024];
	unsigned int m_unIFCPDataLen;

	unsigned char m_ucIPCP_cwodd[128];
	unsigned char m_unIFCP_cweven[128];
	unsigned char m_ucIFCP_k2[128];

	unsigned char m_ucIFCP_Image[128 * 1024];

	File_Info_S m_stPEFFile;
	File_Info_S m_stSTHFile;

	char m_acPEFFileName[256];
	char m_acIFCPFileName[256];
	char m_acLastChipID[8];
};

const unsigned int crc32Table[256] =
{
	0x00000000L, 0x04C11DB7L, 0x09823B6EL, 0x0D4326D9L,
	0x130476DCL, 0x17C56B6BL, 0x1A864DB2L, 0x1E475005L,
	0x2608EDB8L, 0x22C9F00FL, 0x2F8AD6D6L, 0x2B4BCB61L,
	0x350C9B64L, 0x31CD86D3L, 0x3C8EA00AL, 0x384FBDBDL,
	0x4C11DB70L, 0x48D0C6C7L, 0x4593E01EL, 0x4152FDA9L,
	0x5F15ADACL, 0x5BD4B01BL, 0x569796C2L, 0x52568B75L,
	0x6A1936C8L, 0x6ED82B7FL, 0x639B0DA6L, 0x675A1011L,
	0x791D4014L, 0x7DDC5DA3L, 0x709F7B7AL, 0x745E66CDL,
	0x9823B6E0L, 0x9CE2AB57L, 0x91A18D8EL, 0x95609039L,
	0x8B27C03CL, 0x8FE6DD8BL, 0x82A5FB52L, 0x8664E6E5L,
	0xBE2B5B58L, 0xBAEA46EFL, 0xB7A96036L, 0xB3687D81L,
	0xAD2F2D84L, 0xA9EE3033L, 0xA4AD16EAL, 0xA06C0B5DL,
	0xD4326D90L, 0xD0F37027L, 0xDDB056FEL, 0xD9714B49L,
	0xC7361B4CL, 0xC3F706FBL, 0xCEB42022L, 0xCA753D95L,
	0xF23A8028L, 0xF6FB9D9FL, 0xFBB8BB46L, 0xFF79A6F1L,
	0xE13EF6F4L, 0xE5FFEB43L, 0xE8BCCD9AL, 0xEC7DD02DL,
	0x34867077L, 0x30476DC0L, 0x3D044B19L, 0x39C556AEL,
	0x278206ABL, 0x23431B1CL, 0x2E003DC5L, 0x2AC12072L,
	0x128E9DCFL, 0x164F8078L, 0x1B0CA6A1L, 0x1FCDBB16L,
	0x018AEB13L, 0x054BF6A4L, 0x0808D07DL, 0x0CC9CDCAL,
	0x7897AB07L, 0x7C56B6B0L, 0x71159069L, 0x75D48DDEL,
	0x6B93DDDBL, 0x6F52C06CL, 0x6211E6B5L, 0x66D0FB02L,
	0x5E9F46BFL, 0x5A5E5B08L, 0x571D7DD1L, 0x53DC6066L,
	0x4D9B3063L, 0x495A2DD4L, 0x44190B0DL, 0x40D816BAL,
	0xACA5C697L, 0xA864DB20L, 0xA527FDF9L, 0xA1E6E04EL,
	0xBFA1B04BL, 0xBB60ADFCL, 0xB6238B25L, 0xB2E29692L,
	0x8AAD2B2FL, 0x8E6C3698L, 0x832F1041L, 0x87EE0DF6L,
	0x99A95DF3L, 0x9D684044L, 0x902B669DL, 0x94EA7B2AL,
	0xE0B41DE7L, 0xE4750050L, 0xE9362689L, 0xEDF73B3EL,
	0xF3B06B3BL, 0xF771768CL, 0xFA325055L, 0xFEF34DE2L,
	0xC6BCF05FL, 0xC27DEDE8L, 0xCF3ECB31L, 0xCBFFD686L,
	0xD5B88683L, 0xD1799B34L, 0xDC3ABDEDL, 0xD8FBA05AL,
	0x690CE0EEL, 0x6DCDFD59L, 0x608EDB80L, 0x644FC637L,
	0x7A089632L, 0x7EC98B85L, 0x738AAD5CL, 0x774BB0EBL,
	0x4F040D56L, 0x4BC510E1L, 0x46863638L, 0x42472B8FL,
	0x5C007B8AL, 0x58C1663DL, 0x558240E4L, 0x51435D53L,
	0x251D3B9EL, 0x21DC2629L, 0x2C9F00F0L, 0x285E1D47L,
	0x36194D42L, 0x32D850F5L, 0x3F9B762CL, 0x3B5A6B9BL,
	0x0315D626L, 0x07D4CB91L, 0x0A97ED48L, 0x0E56F0FFL,
	0x1011A0FAL, 0x14D0BD4DL, 0x19939B94L, 0x1D528623L,
	0xF12F560EL, 0xF5EE4BB9L, 0xF8AD6D60L, 0xFC6C70D7L,
	0xE22B20D2L, 0xE6EA3D65L, 0xEBA91BBCL, 0xEF68060BL,
	0xD727BBB6L, 0xD3E6A601L, 0xDEA580D8L, 0xDA649D6FL,
	0xC423CD6AL, 0xC0E2D0DDL, 0xCDA1F604L, 0xC960EBB3L,
	0xBD3E8D7EL, 0xB9FF90C9L, 0xB4BCB610L, 0xB07DABA7L,
	0xAE3AFBA2L, 0xAAFBE615L, 0xA7B8C0CCL, 0xA379DD7BL,
	0x9B3660C6L, 0x9FF77D71L, 0x92B45BA8L, 0x9675461FL,
	0x8832161AL, 0x8CF30BADL, 0x81B02D74L, 0x857130C3L,
	0x5D8A9099L, 0x594B8D2EL, 0x5408ABF7L, 0x50C9B640L,
	0x4E8EE645L, 0x4A4FFBF2L, 0x470CDD2BL, 0x43CDC09CL,
	0x7B827D21L, 0x7F436096L, 0x7200464FL, 0x76C15BF8L,
	0x68860BFDL, 0x6C47164AL, 0x61043093L, 0x65C52D24L,
	0x119B4BE9L, 0x155A565EL, 0x18197087L, 0x1CD86D30L,
	0x029F3D35L, 0x065E2082L, 0x0B1D065BL, 0x0FDC1BECL,
	0x3793A651L, 0x3352BBE6L, 0x3E119D3FL, 0x3AD08088L,
	0x2497D08DL, 0x2056CD3AL, 0x2D15EBE3L, 0x29D4F654L,
	0xC5A92679L, 0xC1683BCEL, 0xCC2B1D17L, 0xC8EA00A0L,
	0xD6AD50A5L, 0xD26C4D12L, 0xDF2F6BCBL, 0xDBEE767CL,
	0xE3A1CBC1L, 0xE760D676L, 0xEA23F0AFL, 0xEEE2ED18L,
	0xF0A5BD1DL, 0xF464A0AAL, 0xF9278673L, 0xFDE69BC4L,
	0x89B8FD09L, 0x8D79E0BEL, 0x803AC667L, 0x84FBDBD0L,
	0x9ABC8BD5L, 0x9E7D9662L, 0x933EB0BBL, 0x97FFAD0CL,
	0xAFB010B1L, 0xAB710D06L, 0xA6322BDFL, 0xA2F33668L,
	0xBCB4666DL, 0xB8757BDAL, 0xB5365D03L, 0xB1F740B4L
};
/*
#define INIT (0xffffffffL)
#define XOROT (0xffffffffL)

const unsigned int  g_aucPEFCRC32[256] =
{
0x00000000L, 0x77073096L, 0xEE0E612CL, 0x990951BAL,
0x076DC419L, 0x706AF48FL, 0xE963A535L, 0x9E6495A3L,
0x0EDB8832L, 0x79DCB8A4L, 0xE0D5E91EL, 0x97D2D988L,
0x09B64C2BL, 0x7EB17CBDL, 0xE7B82D07L, 0x90BF1D91L,
0x1DB71064L, 0x6AB020F2L, 0xF3B97148L, 0x84BE41DEL,
0x1ADAD47DL, 0x6DDDE4EBL, 0xF4D4B551L, 0x83D385C7L,
0x136C9856L, 0x646BA8C0L, 0xFD62F97AL, 0x8A65C9ECL,
0x14015C4FL, 0x63066CD9L, 0xFA0F3D63L, 0x8D080DF5L,
0x3B6E20C8L, 0x4C69105EL, 0xD56041E4L, 0xA2677172L,
0x3C03E4D1L, 0x4B04D447L, 0xD20D85FDL, 0xA50AB56BL,
0x35B5A8FAL, 0x42B2986CL, 0xDBBBC9D6L, 0xACBCF940L,
0x32D86CE3L, 0x45DF5C75L, 0xDCD60DCFL, 0xABD13D59L,
0x26D930ACL, 0x51DE003AL, 0xC8D75180L, 0xBFD06116L,
0x21B4F4B5L, 0x56B3C423L, 0xCFBA9599L, 0xB8BDA50FL,
0x2802B89EL, 0x5F058808L, 0xC60CD9B2L, 0xB10BE924L,
0x2F6F7C87L, 0x58684C11L, 0xC1611DABL, 0xB6662D3DL,
0x76DC4190L, 0x01DB7106L, 0x98D220BCL, 0xEFD5102AL,
0x71B18589L, 0x06B6B51FL, 0x9FBFE4A5L, 0xE8B8D433L,
0x7807C9A2L, 0x0F00F934L, 0x9609A88EL, 0xE10E9818L,
0x7F6A0DBBL, 0x086D3D2DL, 0x91646C97L, 0xE6635C01L,
0x6B6B51F4L, 0x1C6C6162L, 0x856530D8L, 0xF262004EL,
0x6C0695EDL, 0x1B01A57BL, 0x8208F4C1L, 0xF50FC457L,
0x65B0D9C6L, 0x12B7E950L, 0x8BBEB8EAL, 0xFCB9887CL,
0x62DD1DDFL, 0x15DA2D49L, 0x8CD37CF3L, 0xFBD44C65L,
0x4DB26158L, 0x3AB551CEL, 0xA3BC0074L, 0xD4BB30E2L,
0x4ADFA541L, 0x3DD895D7L, 0xA4D1C46DL, 0xD3D6F4FBL,
0x4369E96AL, 0x346ED9FCL, 0xAD678846L, 0xDA60B8D0L,
0x44042D73L, 0x33031DE5L, 0xAA0A4C5FL, 0xDD0D7CC9L,
0x5005713CL, 0x270241AAL, 0xBE0B1010L, 0xC90C2086L,
0x5768B525L, 0x206F85B3L, 0xB966D409L, 0xCE61E49FL,
0x5EDEF90EL, 0x29D9C998L, 0xB0D09822L, 0xC7D7A8B4L,
0x59B33D17L, 0x2EB40D81L, 0xB7BD5C3BL, 0xC0BA6CADL,
0xEDB88320L, 0x9ABFB3B6L, 0x03B6E20CL, 0x74B1D29AL,
0xEAD54739L, 0x9DD277AFL, 0x04DB2615L, 0x73DC1683L,
0xE3630B12L, 0x94643B84L, 0x0D6D6A3EL, 0x7A6A5AA8L,
0xE40ECF0BL, 0x9309FF9DL, 0x0A00AE27L, 0x7D079EB1L,
0xF00F9344L, 0x8708A3D2L, 0x1E01F268L, 0x6906C2FEL,
0xF762575DL, 0x806567CBL, 0x196C3671L, 0x6E6B06E7L,
0xFED41B76L, 0x89D32BE0L, 0x10DA7A5AL, 0x67DD4ACCL,
0xF9B9DF6FL, 0x8EBEEFF9L, 0x17B7BE43L, 0x60B08ED5L,
0xD6D6A3E8L, 0xA1D1937EL, 0x38D8C2C4L, 0x4FDFF252L,
0xD1BB67F1L, 0xA6BC5767L, 0x3FB506DDL, 0x48B2364BL,
0xD80D2BDAL, 0xAF0A1B4CL, 0x36034AF6L, 0x41047A60L,
0xDF60EFC3L, 0xA867DF55L, 0x316E8EEFL, 0x4669BE79L,
0xCB61B38CL, 0xBC66831AL, 0x256FD2A0L, 0x5268E236L,
0xCC0C7795L, 0xBB0B4703L, 0x220216B9L, 0x5505262FL,
0xC5BA3BBEL, 0xB2BD0B28L, 0x2BB45A92L, 0x5CB36A04L,
0xC2D7FFA7L, 0xB5D0CF31L, 0x2CD99E8BL, 0x5BDEAE1DL,
0x9B64C2B0L, 0xEC63F226L, 0x756AA39CL, 0x026D930AL,
0x9C0906A9L, 0xEB0E363FL, 0x72076785L, 0x05005713L,
0x95BF4A82L, 0xE2B87A14L, 0x7BB12BAEL, 0x0CB61B38L,
0x92D28E9BL, 0xE5D5BE0DL, 0x7CDCEFB7L, 0x0BDBDF21L,
0x86D3D2D4L, 0xF1D4E242L, 0x68DDB3F8L, 0x1FDA836EL,
0x81BE16CDL, 0xF6B9265BL, 0x6FB077E1L, 0x18B74777L,
0x88085AE6L, 0xFF0F6A70L, 0x66063BCAL, 0x11010B5CL,
0x8F659EFFL, 0xF862AE69L, 0x616BFFD3L, 0x166CCF45L,
0xA00AE278L, 0xD70DD2EEL, 0x4E048354L, 0x3903B3C2L,
0xA7672661L, 0xD06016F7L, 0x4969474DL, 0x3E6E77DBL,
0xAED16A4AL, 0xD9D65ADCL, 0x40DF0B66L, 0x37D83BF0L,
0xA9BCAE53L, 0xDEBB9EC5L, 0x47B2CF7FL, 0x30B5FFE9L,
0xBDBDF21CL, 0xCABAC28AL, 0x53B39330L, 0x24B4A3A6L,
0xBAD03605L, 0xCDD70693L, 0x54DE5729L, 0x23D967BFL,
0xB3667A2EL, 0xC4614AB8L, 0x5D681B02L, 0x2A6F2B94L,
0xB40BBE37L, 0xC30C8EA1L, 0x5A05DF1BL, 0x2D02EF8DL
};
*/

#endif/*PEF_H_*/