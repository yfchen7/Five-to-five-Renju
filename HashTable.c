
#include "HashTable.h"

struct HashPos HashTable[HashSize];

//Generate by Mersenne Twister pseudorandom number generator.
// zobrist
//

unsigned long long psunumber[2][225] = {
	{
		7266447313870364031U,  4946485549665804864U, 16945909448695747420U, 16394063075524226720U,  4873882236456199058U,
		14877448043947020171U,  6740343660852211943U, 13857871200353263164U,  5249110015610582907U, 10205081126064480383U,
		1235879089597390050U, 17320312680810499042U, 16489141110565194782U,  8942268601720066061U, 13520575722002588570U,
		14226945236717732373U,  9383926873555417063U, 15690281668532552105U, 11510704754157191257U, 15864264574919463609U,
		6489677788245343319U,  5112602299894754389U, 10828930062652518694U, 15942305434158995996U, 15445717675088218264U,
		4764500002345775851U, 14673753115101942098U,   236502320419669032U, 13670483975188204088U, 14931360615268175698U,
		8904234204977263924U, 12836915408046564963U, 12120302420213647524U, 15755110976537356441U,  5405758943702519480U,
		10951858968426898805U, 17251681303478610375U,  4144140664012008120U, 18286145806977825275U, 13075804672185204371U,
		10831805955733617705U,  6172975950399619139U, 12837097014497293886U, 12903857913610213846U,   560691676108914154U,
		1074659097419704618U, 14266121283820281686U, 11696403736022963346U, 13383246710985227247U,  7132746073714321322U,
		10608108217231874211U,  9027884570906061560U, 12893913769120703138U, 15675160838921962454U,  2511068401785704737U,
		14483183001716371453U,  3774730664208216065U,  5083371700846102796U,  9583498264570933637U, 17119870085051257224U,
		5217910858257235075U, 10612176809475689857U,  1924700483125896976U,  7171619684536160599U, 10949279256701751503U,
		15596196964072664893U, 14097948002655599357U,   615821766635933047U,  5636498760852923045U, 17618792803942051220U,
		580805356741162327U,   425267967796817241U,  8381470634608387938U, 13212228678420887626U, 16993060308636741960U,
		957923366004347591U,  6210242862396777185U,  1012818702180800310U, 15299383925974515757U, 17501832009465945633U,
		17453794942891241229U, 15807805462076484491U,  8407189590930420827U,   974125122787311712U,  1861591264068118966U,
		997568339582634050U, 18046771844467391493U, 17981867688435687790U,  3809841506498447207U,  9460108917638135678U,
		16172980638639374310U,   958022432077424298U,  4393365126459778813U, 13408683141069553686U, 13900005529547645957U,
		15773550354402817866U, 16475327524349230602U,  6260298154874769264U, 12224576659776460914U,  6405294864092763507U,
		7585484664713203306U,  5187641382818981381U, 12435998400285353380U, 13554353441017344755U,   646091557254529188U,
		11393747116974949255U, 16797249248413342857U, 15713519023537495495U, 12823504709579858843U,  4738086532119935073U,
		4429068783387643752U,   585582692562183870U,  1048280754023674130U,  6788940719869959076U, 11670856244972073775U,
		2488756775360218862U,  2061695363573180185U,  6884655301895085032U,  3566345954323888697U, 12784319933059041817U,
		4772468691551857254U,  6864898938209826895U,  7198730565322227090U,  2452224231472687253U, 13424792606032445807U,
		10827695224855383989U, 11016608897122070904U, 14683280565151378358U,  7077866519618824360U, 17487079941198422333U,
		3956319990205097495U,  5804870313319323478U,  8017203611194497730U,  3310931575584983808U,  5009341981771541845U,
		6930001938490791874U, 14415278059151389495U, 11001114762641844083U,  6715939435439735925U,   411419160297131328U,
		4522402260441335284U,  3381955501804126859U, 15935778656111987797U,  4345051260540166684U, 13978444093099579683U,
		9219789505504949817U,  9245142924137529075U, 11628184459157386459U,  7242398879359936370U,  8511401943157540109U,
		11948130810477009827U,  6865450671488705049U, 13965005347172621081U, 15956599226522058336U,  7737868921014130584U,
		2107342503741411693U, 15818996300425101108U, 16399939197527488760U, 13971145494081508107U,  3910681448359868691U,
		4249175367970221090U,  9735751321242454020U, 12418107929362160460U,   241792245481991138U,  5806488997649497146U,
		10724207982663648949U,  1121862814449214435U,  1326996977123564236U,  4902706567834759475U, 12782714623891689967U,
		7306216312942796257U, 15681656478863766664U,   957364844878149318U,  5651946387216554503U,  8197027112357634782U,
		6302075516351125977U, 13454588464089597862U, 15638309200463515550U, 10116604639722073476U, 12052913535387714920U,
		2889379661594013754U, 15383926144832314187U,  7841953313015471731U, 17310575136995821873U,  9820021961316981626U,
		15319619724109527290U, 15349724127275899898U, 10511508162402504492U,  6289553862380300393U, 15046218882019267110U,
		11772020174577005930U,  3537640779967351792U,  6801855569284252424U, 17687268231192623388U, 12968358613633237218U,
		1429775571144180123U, 10427377732172208413U, 12155566091986788996U, 16465954421598296115U, 12710429690464359999U,
		9547226351541565595U, 12156624891403410342U,  2985938688676214686U, 18066917785985010959U,  5975570403614438776U,
		11541343163022500560U, 11115388652389704592U,  9499328389494710074U,  9247163036769651820U,  3688303938005101774U,
		2210483654336887556U, 15458161910089693228U,  6558785204455557683U,  1288373156735958118U, 18433986059948829624U,
		3435082195390932486U, 16822351800343061990U,  3120532877336962310U, 16681785111062885568U,  7835551710041302304U,
		2612798015018627203U, 15083279177152657491U,  6591467229462292195U, 10592706450534565444U,  7438147750787157163U

	},
	{
		323186165595851698U,  7444710627467609883U,  8473714411329896576U,  2782675857700189492U,  3383567662400128329U,
		3200233909833521327U, 12897601280285604448U,  3612068790453735040U,  8324209243736219497U, 15789570356497723463U,
		1083312926512215996U,  4797349136059339390U,  5556729349871544986U, 18266943104929747076U,  1620389818516182276U,
		172225355691600141U,  3034352936522087096U,  1266779576738385285U,  3906668377244742888U,  6961783143042492788U,
		17159706887321247572U,  4676208075243319061U, 10315634697142985816U, 13435140047933251189U,   716076639492622016U,
		13847954035438697558U,  7195811275139178570U, 10815312636510328870U,  6214164734784158515U, 16412194511839921544U,
		3862249798930641332U,  1005482699535576005U,  4644542796609371301U, 17600091057367987283U,  4209958422564632034U,
		5419285945389823940U, 11453701547564354601U,  9951588026679380114U,  7425168333159839689U,  8436306210125134906U,
		11216615872596820107U,  3681345096403933680U,  5770016989916553752U, 11102855936150871733U, 11187980892339693935U,
		396336430216428875U,  6384853777489155236U,  7551613839184151117U, 16527062023276943109U, 13429850429024956898U,
		9901753960477271766U,  9731501992702612259U,  5217575797614661659U, 10311708346636548706U, 15111747519735330483U,
		4353415295139137513U,  1845293119018433391U, 11952006873430493561U,  3531972641585683893U, 16852246477648409827U,
		15956854822143321380U, 12314609993579474774U, 16763911684844598963U, 16392145690385382634U,  1545507136970403756U,
		17771199061862790062U, 12121348462972638971U, 12613068545148305776U,   954203144844315208U,  1257976447679270605U,
		3664184785462160180U,  2747964788443845091U, 15895917007470512307U, 15552935765724302120U, 16366915862261682626U,
		8385468783684865323U, 10745343827145102946U,  2485742734157099909U,   916246281077683950U, 15214206653637466707U,
		12895483149474345798U,  1079510114301747843U, 10718876134480663664U,  1259990987526807294U,  8326303777037206221U,
		14104661172014248293U, 15531278677382192198U,  3874303698666230242U,  3611366553819264523U,  1358753803061653874U,
		1552102816982246938U, 14492630642488100979U, 15001394966632908727U,  2273140352787320862U, 17843678642369606172U,
		2903980458593894032U, 16971437123015263604U, 12969653681729206264U,  3593636458822318001U,  9719758956915223015U,
		7437601263394568346U,  3327758049015164431U, 17851524109089292731U, 14769614194455139039U,  8017093497335662337U,
		12026985381690317404U,   739616144640253634U, 15535375191850690266U,  2418267053891303448U, 15314073759564095878U,
		10333316143274529509U, 16565481511572123421U, 16317667579273275294U, 13991958187675987741U,  3753596784796798785U,
		9078249094693663275U,  8459506356724650587U, 12579909555010529099U,  7827737296967050903U,  5489801927693999341U,
		10995988997350541459U, 14721747867313883304U,  7915884580303296560U,  4105766302083365910U, 12455549072515054554U,
		13602111324515032467U,  5205971628932290989U,  5034622965420036444U,  9134927878875794005U, 11319873529597990213U,
		14815445109496752058U,  2266601052460299470U,  5696993487088103383U,  6540200741841280242U,  6631495948031875490U,
		5328340585170897740U, 17897267040961463930U,  9030000260502624168U, 14285709137129830926U, 12854071997824681544U,
		15408328651008978682U,  1063314403033437073U, 13765209628446252802U,   242013711116865605U,  4772374239432528212U,
		2515855479965038648U,  5872624715703151235U, 14237704570091006662U,   678604024776645862U, 12329607334079533339U,
		17570877682732917020U,  2695443415284373666U,  4312672841405514468U,  6454343485137106900U,  8425658828390111343U,
		16335501385875554899U,  5551095603809016713U, 11781094401885925035U,  9395557946368382509U,  9765123360948816956U,
		18107191819981188154U, 16049267500594757404U, 16349966108299794199U,  1040405303135858246U,  2366386386131378192U,
		223761048139910454U, 15375217587047847934U, 15231693398695187454U, 12916726640254571028U,  8878036960829635584U,
		1626201782473074365U,  5758998126998248293U, 18077917959300292758U, 10585588923088536745U, 15072345664541731497U,
		3559348759319842667U, 12744591691872202375U,  2388494115860283059U,  6414691845696331748U,  3069528498807764495U,
		8737958486926519702U, 18059264986425101074U,  3139684427605102737U, 12378931902986734693U,   410666675039477949U,
		12139894855769838924U,  5780722552400398675U,  7039346665375142557U,  3020733445712569008U,  2612305843503943561U,
		13651771214166527665U, 16478681918975800939U,   566088527565499576U,  4715785502295754870U,  6957318344287196220U,
		11645756868405128885U, 13139951104358618000U, 17650948583490040612U, 18168787973649736637U,  5486282999836125542U,
		6122201977153895166U, 17324241605502052782U, 10063523107521105867U, 17537430712468011382U, 10828407533637104262U,
		10294139354198325113U, 12557151830240236401U, 16673044307512640231U, 10918020421896090419U, 11077531235278014145U,
		5499571814940871256U,  2334252435740638702U, 18177461912527387031U,  2000007376901262542U,  7968425560071444214U,
		1472650787501520648U,  3115849849651526279U,  7980970700139577536U, 12153253535907642097U,  8109716914843248719U,
		3154976533165008908U,  5553369513523832559U, 10345792701798576501U,  3677445364544507875U, 10637177623943913351U

	}
};