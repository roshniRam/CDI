#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string> 
#include <time.h>
#include <stdio.h>
#include <vector>  
#include <sstream>
#include <iterator>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string.h>
#include <math.h>
#include <unordered_map>

#include "TextAnalysis.h"

using namespace std; 

const char* TextAnalysis::stopwordsArray [] = {"a","b", "c","d","e","f","g","h","j","k","l","m",">>>",">>",">",
    "o","p","q","r","s","t","u","v","w","x","z","y","able","about","across","after","all","almost","also","am",
    "among","an","and","any","are2706","as","at","be","because","been","but","by","can","cannot","could","dear",
    "did","do","does","either","else","ever","every","for","from","get","got","had","he","her",
    "hers","him","his","how","however","i","if","in","into","is","its","just","let","like",
    "likely","may","me","might","most","must","my","neither","no","nor","not","of","off","often","on","only",
    "or","other","our","own","rather","said","say","says","she","should","since","so","some","than","that",
    "the","their","them","then","there","these","they","tis","to","too","twas","us","wants","was","we",
    "were","what","when","where","which","while","who","whom","why","will","with","would","yet","you","your",
    "a","able","about","across","after","aint","all","almost","also","am","among","an","and",
    "any","are","arent","as","at","be","because","been","but","by","can","cant","cannot","could","couldve",
    "couldnt","dear","did","didnt","do","does","doesnt","dont","either","else","ever","every","for",
    "from","get","got","hasnt","have","he","hed","hell","hes","her","hers","him","his","how",
    "howd","howll","hows","however","i","id","ill","im","ive","if","in","into","is","isnt",
    "just","least","let","like","likely","may","me","might","mightve","mightnt","most","mustve",
    "mustnt","my","neither","no","nor","not","of","off","often","on","only","or","other","our","own",
    "rather","said","say","says","shant","she","shed","shell","shes","should","shouldve","shouldnt",
    "since","so","some","than","that","thatll","thats","the","their","them","then","there","theres"
    ,"they","theyd","theyre","this","tis","to","too","twas","us","wants","was",
    "wasnt","we","wed","well","were","were","werent","what","whatd","whats","whend","whenll",
    "whens","where","whered","wherell","wheres","which","who","whod","wholl","whos","whom",
    "whyd","whyll","whys","with","wont","would","wouldve","wouldnt","yet","you","youd",
    "youll","youre","youve","aint","arent","cant","couldve","couldnt","didnt",
    "doesnt","dot","hes","howd","howll","hows","id","ill","im","ive","isnt","its","mightve",
    "mightnt","shant","shed","shell","shes","shouldve","shouldnt","thatll","thats","theres",
    "theyd","wasnt","wed","well","were","werent","whatd","whats",
    "whered","wherell","wheres","whod","wholl","whos","wont","wouldve",
    "wouldnt","youd","youll","youre","youve","I","com","de","en","la","und","www", "inhibit","limits" ,
    "throttling","set", "review", "cause", "old","able","about","above","abroad","according","accordingly",
    "against","abroad","ahead","aint","all","allow","allows","almost","alone","along","alongside","already",
    "also","although","always","am","amid","amidst","among","amongst","alongside","and","another","any",
    "anybody","anyhow","anyone","anything","anyway","anyways","anywhere","apart","appear","appreciate",
    "appropriate","are","arent","around","as","anyways","aside","ask","asking","associated","at","available",
    "away","awfully","back","backward","backwards","be","became","because","become","becomes","becoming",
    "been","back","beforehand","begin","behind","being","believe","below","beside","besides","best","better",
    "between","beyond","both","brief","but","by","came","can","best","cant","cant","caption","cause",
    "causes","certain","certainly","changes","clearly","co","co.","com","come","comes","concerning",
    "consequently","consider","clearly","contain","containing","contains","corresponding","could","couldnt",
    "course","cs","currently","dare","darent","definitely","described","despite","did","didnt","different",
    "directly","currently","does","doesnt","doing","done","dont","down","downwards","during","each","edu",
    "eg","eight","eighty","either","else","elsewhere","end","ending","each","entirely","especially","et",
    "etc","even","ever","evermore","every","everybody","everyone","everything","everywhere","ex","exactly",
    "example","except","fairly","far","everybody","few","fewer","fifth","first","five","followed","following",
    "follows","for","forever","former","formerly","forth","forward","found","four","from","further","for",
    "get","gets","getting","given","gives","go","goes","going","gone","got","gotten","greetings","hase",
    "hadnt","half","happens","hardly","has","gone","havent","having","he","hed","hell","hello",
    "help","hence","her","here","hereafter","hereby","herein","heres","hereupon","hers","herself","hence",
    "hi","him","himself","his","hither","hopefully","how","howbeit","however","hundred","ie","if",
    "ignored","im","immediate","in","however","inc","inc.","indeed","indicate","indicated","it"
    "indicates","inner","inside","insofar","instead","into","inward","is","isnt","it","itd","itll",
    "insofar","itself","ive","just","k","keep","keep","keeps","kept","know","known","knows","last",
    "lately","later","latter","latterly","less","know","let","lets","like","liked","likely",
    "likewise","little","look","looking","looks","low","lower","ltd","made","mainly","make","makes","many",
    "looking","maybe","maynt","me","mean","meantime","meanwhile","merely","might","mightnt","mine","minus",
    "miss","more","moreover","most","mostly","mr","mrs","mightnt","must","mustnt","my","myself","name",
    "namely","nd","near","nearly","necessary","need","neednt","needs","neither","never","neverf","neverless",
    "nevertheless","nearly","next","nine","ninety","no","nobody","non","none","nonetheless","noone",
    "no-one","nor","normally","not","nothing","notwithstanding","novel","now","nowhere","noone","of","off",
    "often","oh","ok","okay","old","on","once","one","ones","ones","only","onto","opposite","or","other",
    "others","once","ought","oughtnt","our","ours","ourselves","out","outside","over","overall","own",
    "particular","particularly","past","per","perhaps","placed","please","plus","overall","presumably",
    "probably","provided","provides","que","quite","qv","rather","rd","re","really","reasonably","recent",
    "recently","regarding","regardless","regards","relatively","rd","right","round","said","same","saw",
    "say","saying","says","second","secondly","see","seeing","seem","seemed","seeming","seems","seen","self",
    "second","sensible","sent","serious","seriously","seven","several","shall","shant","she","shed",
    "shell","shes","should","shouldnt","since","six","so","some","she","someday","somehow","someone",
    "something","sometime","sometimes","somewhat","somewhere","soon","sorry","specified","specify",
    "specifying","still","sub","such","sup","sure","soon","taken","taking","tell","tends","th","than","thank",
    "thanks","thanx","that","thatll","thats","thats","thatve","the","their","theirs","them","thanx","then",
    "thence","there","thereafter","thereby","thered","therefore","therein","therere","theres",
    "theres","thereupon","thereve","they","theyd","theyll","therell","theyve","thing","things",
    "think","third","thirty","thorough","thoroughly","those","though","three","through","throughout",
    "thru","thus","till","to","thoroughly","too","took","toward","towards","tried","tries","truly","try",
    "trying","twice","two","un","under","underneath","undoing","unfortunately","unless","trying",
    "unlikely","until","unto","up","upon","upwards","us","use","used","useful","uses","using","usually",
    "v","value","various","versus","very","used","viz","vs","want","wants","was","wasnt","way","we","wed",
    "welcome","well","well","went","were","were","werent","weve","what","wed","whatll","whats",
    "whatve","when","whence","whenever","where","whereafter","whereas","whereby","wherein","wheres",
    "whereupon","wherever","whether","which","whichever","whereas","whither","who","whod",
    "whoever","whole","wholl","whom","whomever","whos","whose","why","willing","wish","with",
    "within","without","wonder","whos","would","wouldnt","yes","yet","you","youd","youll","your",
    "youre","yours","yourself","yourselves","youve", "across","actually","adj","after","afterwards",
    "re", "-lrb-", "``" , "`", "-rrb-", "mccain", "thi" , "sai","starr",
     "%" , "cnn" , "wa", "-LRB-", "-RRB-", "rrb", "lrb" , "governments","again", 
    "moldova", "committee", "tension", "applause", "yesterdays", "yesterday", "issue", "oil",
    "cnn.com", "council", "wave","escalation","hail", "newsroom","milton","happen" ,//cnn.com\/fan", 
    "nightfall","effort", "thousand","ambassador","greater","sort ", "day", //"\/", 
    "days","large","michael", "phelps" ,"reporter","akaiwa","hayes","dr.", "john", "curran","jatropha", "san", 
    "mr.", "ms.","gori", "south","north","west","east", "correspondent", "matthew", "chance","iphone","diego",
    "elbow", "grease","ad", "ph","...", "harri", "southern" , "isaac", "hayes" , "bachmans",
    "barbara", "sovereignty", "f.", "whitfield" , "large", "scale" , "williams", "condoleezza", "rice" ,"barack" ,
    "obama", "xxix", "caylee" , "casey" ,"surprise" , "new" ,"nan" , "sunday", "ura", "saturday","viewers"
    "dr" , "iii" , "dan" , "subnav" , "mutant" , "live" , "det" , "onus" , "rfi" , "heidi", "collin" , "harris"
    "tony" , "cam" , "gonna","sanjay","gupta","mmviii","wow","breaking","news","cbw","inn","exclusive","pixies"
    "aussie","amass","elise","call","free","coverage","developing","story", "before","kabc","wanna"
    "smm","hour","vause", "ae"};

TextAnalysis::TextAnalysis(){}
TextAnalysis::~TextAnalysis(){}

double factorial(int n)
{
    if(n <= 1)
    {
        return 1;
    }
    else
    {
        double fact = 1;
        for(int i = 1; i <= n; i++)
        {
            fact = fact * i;
        }
        return fact;
    }
}

// getline just doesn't work..............

int getLineNew(istream &stream, string& result)
{
    result.clear();

    do 
    {
        char cc[10];
        //char c = 0;

        cc[0] = 0;
        cc[1] = 0;

        stream.get(cc[0]);
        char c = cc[0];

        if (c == ' ' && result.length() == 0)
            continue;

        if (c == '\n'|| c == 13 || c == 10 )
        { //|| c == 13 || c == 10 || c=='DA'
            if (result.length() == 0)
                continue;
            break;
        }

        if (c == 0)
            break;

        result += string(cc);

    } while(true);

    return result.length();
}

int getLine(istream &stream, string& result)
{
    result.clear();

    do {
        char cc[10];
        // char c = 0;

        cc[0] = 0;
        cc[1] = 0;

        stream.get(cc[0]);
        char c = cc[0];

        //printf("%d\n", c);

        if (c == ' ' && result.length() == 0)
            continue;

        if (c == '\n') 
        { //|| c == 13 || c == 10
            if (result.length() == 0)
                continue;

            break;
        }

        if (c == 0)
            break;

        result += string(cc);

    } while(true);

    return result.length();
}

void TextAnalysis::TopicOnWebArticle(
        vector<TopicElements>& ArticleTopicInfo,
        string list_file4,
        string list_file2)
{

    ifstream DocLists; 
    ifstream ifs;
    string str , DocumentFileName;  
    DocLists.open(list_file4.c_str(), ios::in);
    if (!DocLists.is_open())
    {
        cout<<"File in DocLists NOT opened"<<endl;
    }

    ofstream StoryTopic;
    StoryTopic.open ("StoryTopicForRussia.txt");
    size_t found;

    while (!DocLists.eof() && DocLists.good())
    {

        string bufferstr = "";
        getLineNew(DocLists, bufferstr);
        DocumentFileName = (list_file2 + bufferstr);
        ifs.open(DocumentFileName.c_str() , ios::in);
        if (!ifs.is_open())
        {
            cout<<"File in DocumentFileName NOT opened"<<endl;
        }

        int k=0;
        while (!ifs.eof() && ifs.good() )
        {
            string bufferstr = "";
            getLineNew(ifs, bufferstr);
            str = (bufferstr);
            if (k < 3)
            {
                found = str.find('.');
                if (found < 500 && k > 0)
                {
                    str = str.substr ( 0, found + 1 );
                }
                if (k == 0)
                {
                    str = "<" + str + ">" + "<www.kommersant.com>";
                }
                StoryTopic << str << endl;
                k++;
            }
        }       
        ifs.close();
    }
    StoryTopic.close();
}

vector<Triplet> TextAnalysis::ReadTripletsFile(string tripletsFilename)
{
    ifstream ifs;
    ifs.open(tripletsFilename.c_str(), ios::in);
    size_t found , found1 , found2 ;
    string str, str2 ;
    vector<string> tokens;

    if (!ifs.is_open())
    {
        cout << "Cannot open triplets file:";
        cout << tripletsFilename << endl;        
        //EXCEPTION_TRIPLETS_FILE_CANNOT_OPEN;
    }

    vector<Triplet> storyWordInfo;
    while (!ifs.eof()  && ifs.good())
    {
        Triplet entry;
        char buffer[2048];
        ifs.getline(buffer, 2048);
        str = (buffer);
        found = str.find("<");
        found1 = str.find("/VP");
        found2 = str.find("/NP");

        if ( str != "" )
        {
            if (found < 250 || found1 < 250)
            {
                if (found == 0 )
                {

                    found = str.find('>');
                    found1 = str.find('/' );
                    str2 = str.substr ( 0, found1 - 1 );
                    tokens.push_back(str2);

                    found = str.find("<story>");
                    if (found == 0)
                        entry.StoryTopicName = (str2.substr ( 0, str2.size()));

                    found = str.find("<start>");
                    if (found == 0){
                        str2 = str2.substr ( 0, str2.size() );
                        entry.StoryTimeStart = (str2);}

                    found = str.find("<end>");
                    if (found == 0){
                        str2 = str2.substr ( 0, str2.size() );
                        entry.StoryTimeEnd = (str2);}

                }
                else if (found1 < 200  && found2 < 200 )
                {
                    str2 = str.substr (found2 + 4, (found1 - found2 )- 4 ); 
                    entry.Verb_Ph = (str2);
                    str2 = str.substr (0 , found2 );
                    entry.Non_Ph1 = (str2);
                    str2 = str.substr (found2+4 , str.size() );
                    found = str2.find("/NP");
                    str2 = str2.substr (0 , found );
                    found1 = str2.find("VP");
                    str2 = str2.substr (found1+3 , str2.size() );
                    found1 = str2.find("PP;");
                    
                    if (found1 <= 50)
                    {
                        str2 = str2.substr (found1 + 3 , str2.size() );
                    }
                    found1 = str2.find("/PRT;");
                    
                    if (found1 <= 50)
                    {
                        str2 = str2.substr (found1 + 6 , str2.size() );
                    }
                    entry.Non_Ph2 = (str2);
                }
                storyWordInfo.push_back(entry);
            }
        }
    }
    return storyWordInfo;
}

void TextAnalysis::FirstSentAsTopic(string fileName,
    vector<TopicElements>& StoryTopicInfo)
{

    ifstream ifs;
    ifs.open(fileName.c_str(), ios::in);
    size_t found0, found , found1 , found2, found3 ,found4 , found5, found6 , found7, foundEnd ;
    string str, str2 ;
    int ind = 0 , ind1 = 0;
    TopicElements entry;
    
    while (!ifs.eof() && ifs.good())
    {

        char buffer[2048];
        ifs.getline(buffer, 2048);
        str = (buffer);

        found0 = str.find("<");  //str != "" && 
        found1 = str.find("/NP");

        if (found0 != 0 && str != "" && found1 > 500 && ind == 0 )
        {
            found = str.find("following");
            found1 = str.find("we've");
            found2 = str.find("follow");
            found3 = str.find("breaking");
            found4 = str.find("Thanks");
            found5 = str.find("NEWSROOM");
            found6 = str.find("live");
            found7 = str.find("developing");
            if ( found > 500 && found1 > 500 && found2 > 500 && found3 > 500 &&
                 found4 > 500 && found5 > 500 && found6 > 500 && found7 > 500 )
            {

                const char* array[] = {"MARCIANO:","Well,", "your","Then,","(APPLAUSE)","CHETRY:", 
                "(END", "VIDEO" , "CLIP)" , "MARCIANO:" , "MD:" , "He" , "(COMMERCIAL","BREAK)",
                "CHETRY", ":" ,"they're" , ",", "Yes" , "COLLINS:" , "HARRIS:" };
                vector<string> removeList(array, array + sizeof array / sizeof array[0]);
            
                vector<string> words;
                istringstream iss(str);
                string wholeString;
                copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));

                for(int kk=0; kk < words.size(); kk++)
                {
                    for (int jj=0; jj < removeList.size(); jj++)
                    {
                        if (words[kk].compare(removeList[jj]) == 0)
                        {
                            words[kk] = "" ;
                        }
                    }
                }
                
                wholeString.clear();
                for(int kk=0; kk < words.size(); kk++)
                {
                    if (words[kk] != "")
                    {
                            wholeString = wholeString + " " + words[kk] ;
                    }
                }

                entry.FullTopicName = wholeString;  
                ind = 1;
                //StoryTopic << wholeString << endl;

            }
        }   

        found1 = str.find("/NP");
        if (ind ==1 && ind1 == 0 && found1< 500)
        {
            found2 = str.find("/VP");
            str2 = str.substr( 0 , found1 );
            entry.Non_Ph1 = str2;
            str2 = str.substr(found1+4 , str.size() );
            found2 = str2.find("/VP");
            str2 = str2.substr(0,found2);
            entry.Verb_Ph = str2;
            ind1=1;
        }
        
        if (found0 == 0 )
        {
            found = str.find("<story>");
            if (found == 0)
            {
                str2 = str.substr(7 , str.size() );
                found1 = str2.find("<");
                str2 = str2.substr(0 , found1) ;
                entry.StoryTopicName = str2;
                //StoryTopic << str << endl;
            }
            found = str.find("<start>");
            if (found == 0)
            {
                str2 = str.substr(7 , str.size() );
                found1 = str2.find("<");
                str2 = str2.substr(0 , found1) ;
                entry.StoryTimeStart = str2;
                //StoryTopic << str << endl;
            }
            foundEnd = str.find("<end>");
            if (foundEnd == 0)
            {
                str2 = str.substr(5 , str.size());
                found1 = str2.find("<");
                str2 = str2.substr(0 , found1);

                entry.StoryTimeEnd = str2;
                ind = 0;
                ind1 =0;    
                if ( entry.FullTopicName != "" && entry.StoryTimeEnd != "" && entry.StoryTimeStart != "" && entry.StoryTopicName != "")
                {
                    StoryTopicInfo.push_back(entry);
                }
            }
        }
    }
}

//output: StoryTopic.txt
void TextAnalysis::StoryTopic(const vector<TopicElements>& storyInfoTags,
    const vector<TopicElements>& StoryTopicInfo,
    const vector<TopicElements>& resourceGoalTags)
{
    ofstream StoryTopic;
    StoryTopic.open ("StoryTopic.txt");
    vector<TopicElements> storyInfoFull;
    

    string StoryTimeStart;
    string StoryTimeEnd;
    string StoryTopicName;
    string FullTopicName;
    string Non_Ph1;
    string Verb_Ph;
    vector<string> Person;
    vector<string> Location;

    // combine person and location tags
    for (int i=0; i < storyInfoTags.size(); i++)
    {
        for ( int j=0; j < StoryTopicInfo.size(); j++)
        {
            if (storyInfoTags[i].StoryTimeStart == StoryTopicInfo[j].StoryTimeStart)
            {
                TopicElements entry;
                entry.StoryTimeStart = storyInfoTags[i].StoryTimeStart;
                entry.StoryTimeEnd = storyInfoTags[i].StoryTimeEnd;
                entry.StoryTopicName = storyInfoTags[i].StoryTopicName;
                entry.FullTopicName = StoryTopicInfo[j].FullTopicName;
                entry.Non_Ph1 = StoryTopicInfo[j].Non_Ph1;
                entry.Verb_Ph = StoryTopicInfo[j].Verb_Ph;
                entry.Person = storyInfoTags[i].Person;
                entry.Location = storyInfoTags[i].Location;
                storyInfoFull.push_back(entry);
            }   
        }
    }

    // combine resources and goal tags
    for (int i=0; i < storyInfoFull.size(); i++)
    {
        for (int j=0; j < resourceGoalTags.size(); j++)
        {
            if (storyInfoFull[i].StoryTimeStart == resourceGoalTags[j].StoryTimeStart)
            {
                storyInfoFull[i].Resources = resourceGoalTags[j].Resources;
                storyInfoFull[i].Goal = resourceGoalTags[j].Goal;
            }   
        }
    }

    // output
    for (int i=0; i < storyInfoFull.size(); i++)
    {
        vector<string> Per = storyInfoFull[i].Person;
        vector<string> Loc = storyInfoFull[i].Location;
        vector<string> resources = storyInfoFull[i].Resources;
        vector<string> goal = storyInfoFull[i].Goal;
        string Person ="";
        string Location="";
        string resource ="";
        string goals ="";

        if (Per.size() != 0){
            for (int j=0; j<Per.size(); j++){
                if (Per[j] !="HEIDI COLLINS" || Per[j] !="LARRY"){
                Person = Per[j]+","+Person;}
            }
        }

        if (Loc.size() != 0){
            for (int j=0; j<Loc.size(); j++){
                Location = Loc[j]+","+Location;
            }
        }
        if (resources.size() != 0){
            for (int j=0; j<resources.size(); j++){
                resource = resources[j]+","+resource;
            }
        }
        if (Loc.size() != 0){
            for (int j=0; j<goal.size(); j++){
                goals = goal[j]+","+goals;
            }
        }

        // cout <<"goals   " << goals <<" resource   "<< resource<< endl; 
    }



    for ( int i=0; i < storyInfoFull.size(); i++)
    {
        vector<string> Per = storyInfoFull[i].Person;
        vector<string> Loc = storyInfoFull[i].Location;
        vector<string> resources = storyInfoFull[i].Resources;
        vector<string> goal = storyInfoFull[i].Goal;
        string Person ="";
        string Location="";
        string resource ="";
        string goals ="";
        if (Per.size() != 0){
            for (int j=0; j<Per.size(); j++){
                if (Per[j] !="HEIDI COLLINS" || Per[j] !="LARRY"){
                Person = Per[j]+","+Person;}
            }
        }

        if (Loc.size() != 0){
            for (int j=0; j<Loc.size(); j++){
                Location = Loc[j]+","+Location;
            }
        }
        if (resources.size() != 0){
            for (int j=0; j<resources.size(); j++){
                resource = resources[j]+","+resource;
            }
        }
        if (Loc.size() != 0){
            for (int j=0; j<goal.size(); j++){
                goals = goal[j]+","+goals;
            }
        }

        StoryTopic << storyInfoFull[i].StoryTimeStart <<"|"<< 
            storyInfoFull[i].StoryTimeEnd << 
            "|Topic|Text="<< storyInfoFull[i].FullTopicName<< endl; 

        StoryTopic << storyInfoFull[i].StoryTimeStart <<"|"<< 
            storyInfoFull[i].StoryTimeEnd <<
            "|Topic|Agent= "<<storyInfoFull[i].Non_Ph1<< endl; 

        StoryTopic << storyInfoFull[i].StoryTimeStart <<"|"<< 
            storyInfoFull[i].StoryTimeEnd <<
            "|Topic|Action= "<<storyInfoFull[i].Verb_Ph<< endl; 

        StoryTopic << storyInfoFull[i].StoryTimeStart <<"|"<< 
            storyInfoFull[i].StoryTimeEnd <<
            "|Topic|Location= "<<Location<< endl; 

        StoryTopic << storyInfoFull[i].StoryTimeStart <<"|"<< 
            storyInfoFull[i].StoryTimeEnd <<
            "|Topic|Person= "<<Person<< endl; 

        StoryTopic << storyInfoFull[i].StoryTimeStart <<"|"<< 
            storyInfoFull[i].StoryTimeEnd <<
            "|Topic|Resources= "<<resource<< endl; 

        StoryTopic << storyInfoFull[i].StoryTimeStart <<"|"<< 
            storyInfoFull[i].StoryTimeEnd <<
            "|Topic|Goal= "<<goals<< endl; 
    }

    StoryTopic.close();
}

vector<TopicElements> TextAnalysis::ReadFullDocument(string newsListFilename)
{
    vector<TopicElements> Story_InfoForTag;

    ifstream DocLists,ifs;
    string str, str1, str2, str3,StartPoint, words;

    DocLists.open(newsListFilename.c_str(), ios::in);
    if (!DocLists.is_open())
    {
        cout << "news list NOT opened"<<endl;
        throw -1;
    }
    size_t found , found1, found2, found3 ;
    vector<string> Story_Word;
    TopicElements entry;
    int Iindix=0 , Iindix1=0, Iindix2=0;
    while (!DocLists.eof() && DocLists.good())
    {
        string bufferstr = "";
        getLineNew(DocLists, bufferstr);
        str = (bufferstr);

        string Year,Month,Day;
        if(str != "")
        {
            Year = str.substr(0 , 4);
            Month = str.substr(5 , 2);
            Day = str.substr(8 , 2);
        }

        // /sweep/2008/2008-08/2008-08-08/
        string FileName = ("/sweep/"+Year+"/"+Year+"-"+Month+"/"+Year+"-"+Month+"-"+Day+"/" + str +".txt");
        ifs.open(FileName.c_str(), ios::in);
        if (!ifs.is_open()) cout<<"FileName File NOT opened"<<endl;
        Iindix2=0;

        while (!ifs.eof() && ifs.good() )
        {
            string bufferstr = "";
            getLineNew(ifs, bufferstr);
            str = (bufferstr);

            found = str.find("SegStart");
            found1 = str.find("SegStart-NEW");

            if ( found==0 && Iindix2==0)
            {
                StartPoint = str.substr(9 , 18);
                Iindix2=1;
            }
            if ( found == 0 && Iindix ==0 && found1 != 0)
            {
                string Cat_Topic = str.substr(28 , str.size());
                found1 = Cat_Topic.find("|");
                string Cat = Cat_Topic.substr(0 , found1);
                string Top = Cat_Topic.substr(found1+1 , Cat_Topic.size() );
                string Start = str.substr(9 , 18);
                entry.StoryTimeStart = StartPoint;

                entry.StoryTopicName = Cat +"|"+Top;
                Iindix = 1;
            }

            found1 = str.find("SegEnd");
            found = str.find("SegEnd-NEW");
            if ( found1 == 0 && Iindix1 ==0 && found != 0 )
            {
                string EndPoint = str.substr(7 , 18);
                entry.StoryTimeEnd = EndPoint;
                Iindix1 = 1;
            }
            found2 = str.find("CCO");
            if ( found2 == 0)
            {
                string Word_inEachline= str.substr( 23 , str.size() );
                words = words + Word_inEachline + " ";
            }
            if (found1 == 0 && found != 0 ) {   
                entry.FullTopicName = words;
                Story_InfoForTag.push_back(entry);
                Iindix = 0;
                Iindix1 = 0;
                Iindix2 = 0;
                words.clear();
            }
        }
        ifs.close();
    }
    return Story_InfoForTag;
}

//output: storyTagInfo.txt
//output FullDocument.txt
void TextAnalysis::ReadTagFromFile(vector<TopicElements>& Story_InfoForTag)
{

    ofstream fout_fulldoc;
    fout_fulldoc.open ("output/FullDocument.txt");
    for (int i=0; i < Story_InfoForTag.size(); i++)
    {
        fout_fulldoc << "<story>" << Story_InfoForTag[i].StoryTopicName << endl;
        fout_fulldoc << "<start>" << Story_InfoForTag[i].StoryTimeStart << endl;
        fout_fulldoc << Story_InfoForTag[i].FullTopicName << endl;
        fout_fulldoc << "<end>" <<Story_InfoForTag[i].StoryTimeEnd << endl;
    }
    fout_fulldoc.close();
            
    string CMD_annotate = "./annotate output/FullDocument.txt output/FullDocument_tagged.txt true Config/allFeaturesBigTrainingSet.config"; 
    system(CMD_annotate.c_str());

    
    ofstream StoryTag;
    StoryTag.open("StoryTagInfo.txt");      

    
    vector<string> Person;
    vector<string> Miscellaneous ;
    vector<string> Organization;
    vector<string> Location;
    vector<string> Resources;
    vector<string> Goal;

    vector<int> StoryInDocument;
    int count = 0 , total_count = 0 , Indix = 0 , Indix1 = 0;

    ifstream ifs;
    ifs.open("output/FullDocument_tagged.txt", ios::in);
    while (!ifs.eof() && ifs.good())
    {
        string str2, str_compare = "";

        TaggedElements Tagged;
        char buffer[2048];
        ifs.getline(buffer, 2048);
        string str = (buffer);
        string StrRefrence = str;
        size_t found1;
        size_t found = str.find("<");
        size_t found_per = str.find("[PER");
        size_t found_organization = str.find("[ORG");
        size_t found_misc = str.find("[MISC");
        size_t found5 = 0 ;
        size_t found_end = str.find( "<end>");
        size_t found_loc = str.find("[LOC"); 
        size_t found_story = str.find("<story>");
        size_t found_start = str.find("<start>");

        if ( found_end == 0 )
        {
            StoryInDocument.push_back(count);
            total_count = total_count + count;
            count = 0;
        }

        if ( str != "" ||  found_story < 250 || found_start < 250 || found_end <250 )
        { // found1 > 250 &&
            count++;

            if (found_story < 250 || found_start < 250 || found_end <250)
            {
                StoryTag << str << endl;
            }
            if (str_compare != str)   /*(str_compare.compare(str) != 0)*/
            {
                if (found > 500 && Indix == 0 && str != ""  )
                {
                    str_compare = str;
                }

                if (found_per < 500 )
                { 
                    found = str.find(']');
                    while (found5 < 1000 )
                    {
                        if (found < found_per)
                        {           
                            while(found < found_per )
                            {
                                str2 = str.substr(found+1,str.size());
                                str = str2;
                                found = str.find(']');
                                found_per = str.find("[PER");
                            }
                            found1 = found - found_per;
                            str2 = str2.substr ( found_per  , found1 +1);

                            found1 = str2.find(":");
                            if (found1 < 50 )
                            {
                                str2 = str2.substr ( found1  , str2.size() -1);
                            }
                            Person.push_back(str2);

                            StoryTag << str2 << endl;//Tagged.Per = str2;
                            str = str.substr ( found + 1  , str.size() );
                            found5 = str.find("[PER");
                            found_per = found5;
                            found = str.find(']');
                        }
                        else
                        {
                            found1 = found - found_per;
                            str2 = str.substr ( found_per  , found1 +1);
                            found1 = str2.find(":");
                            if (found1 < 50 )
                            {
                                str2 = str2.substr ( 0 , found1 );
                                str2 = str2 + "]";
                            }
                        
                            Person.push_back(str2);
                            StoryTag << str2 << endl;
                            str2 = str.substr ( found + 1  , str.size());
                            str = str2;
                            found5 = str.find("[PER");
                            found_per = found5;
                            found = str.find(']');
                        }
                    }
                }
                if ( found_organization < 500 )
                {
                    str = StrRefrence;
                    found5 = 0;
                    found = str.find(']');
                    while (found5 < 1000 )
                    {
                        if ( found < found_organization )
                        {
                            while ( found < found_organization )
                            {
                                str2 = str.substr ( found+1  , str.size());
                                str = str2;
                                found = str.find(']');
                                found_organization = str.find("[ORG");
                            }
                            found1 = found - found_organization;
                            str2 = str2.substr ( found_organization  , found1 +1);
                            Organization.push_back(str2);
                            StoryTag << str2 << endl;//Tagged.Per = str2;
                            str = str.substr ( found + 1  , str.size() );
                            found5 = str.find("[ORG");
                            found_organization = found5;
                            found = str.find(']');
                        }
                        else
                        {
                            found1 = found - found_organization;
                            str2 = str.substr ( found_organization  , found1 +1);
                            Organization.push_back(str2);
                            StoryTag << str2 << endl;
                            str2 = str.substr ( found + 1  , str.size());
                            str = str2;
                            found5 = str.find("[ORG");
                            found_organization = found5;
                            found = str.find(']');
                        }
                    }
                }
                if ( found_misc < 500 )
                {
                    found5 = 0;
                    str = StrRefrence;
                    found = str.find(']');
                    while (found5 < 1000 )
                    {
                        if ( found < found_misc )
                        {                       
                            while ( found < found_misc )
                            {
                                str2 = str.substr ( found+1  , str.size());
                                str = str2;
                                found = str.find(']');
                                found_misc = str.find("[MISC");
                            }
                            found1 = found - found_misc;
                            str2 = str2.substr ( found_misc  , found1 +1);
                            Miscellaneous.push_back(str2);
                            StoryTag << str2 << endl;//Tagged.Per = str2;
                            str = str.substr ( found + 1  , str.size() );
                            found5 = str.find("[MISC");
                            found_misc = found5;
                            found = str.find(']');
                        }
                        else
                        {
                            found1 = found - found_misc;
                            str2 = str.substr ( found_misc  , found1 +1);
                            Miscellaneous.push_back(str2);
                            StoryTag << str2 << endl;
                            str2 = str.substr ( found + 1  , str.size());
                            str = str2;
                            found5 = str.find("[MISC");
                            found_misc = found5;
                            found = str.find(']');
                        }
                    }
                }
                if (found_loc < 500)
                {
                    found5 = 0;
                    str = StrRefrence;
                    found = str.find(']');
                    while (found5 < 1000 )
                    {
                        if ( found < found_loc )
                        {                       
                            while ( found < found_loc )
                            {
                                str2 = str.substr ( found+1  , str.size());
                                str = str2;
                                found = str.find(']');
                                found_loc = str.find("[LOC");
                            }
                            found1 = found - found_loc;
                            str2 = str2.substr ( found_loc  , found1 +1);
                            Location.push_back(str2);
                            StoryTag << str2 << endl;//Tagged.Per = str2;
                            str = str.substr ( found + 1  , str.size() );
                            found5 = str.find("[LOC");
                            found_loc = found5;
                            found = str.find(']');
                        }
                        else
                        {
                            found1 = found - found_loc;
                            str2 = str.substr ( found_loc  , found1 +1);
                            Location.push_back(str2);
                            StoryTag << str2 << endl;
                            str2 = str.substr ( found + 1  , str.size());
                            str = str2;
                            found5 = str.find("[LOC");
                            found_loc = found5;
                            found = str.find(']');
                        }
                    }
                }
            }
        }
    }
    StoryTag.close();
}

vector<TopicElements> TextAnalysis::ReadTag_ResourceGoal(const vector<TopicElements>& storyInfoForTag)
{   
    vector<TopicElements> resourceGoalTag;

    const char* resource_array[] = {"TROOPS:","AIRCRAFTS", "TANKS","MILITARY,","ARMS","REARMING", 
    "PEACE KEEPERS", "SOLDIERS" , "SOLDIER" , "TROOP", "BOMBS", "SEPARATISTS FORCES", "ARMORED  VEHICLES",
    "MILITARY AIRCRAFT", "REINFORCEMENTS","WARPLANES"  };
    set<string> resourceList(resource_array, resource_array + sizeof resource_array / sizeof resource_array[0]);

    const char* goal_array[] = {"SELF-DEFENSE","ETHNIC CLEANSING,","CRUSHING DEMOCRACY","ETHNIC  CLEANSING", 
    "OIL", "ENERGY" , "Occupy" , "control" , "CRUSHING DEMOCRACY" , "NATO MEMBERSHIP", "HUMANITARIAN SUPPORT"};
    set<string> goalList(goal_array, goal_array + sizeof goal_array / sizeof goal_array[0]);

    for (int i=0; i < storyInfoForTag.size(); i++)
    {
        vector<string> topicWords;
        istringstream iss(storyInfoForTag[i].FullTopicName);
        copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(topicWords));

        vector<string> resources;
        vector<string> goals;

        for(int k=0; k < topicWords.size(); k++)
        {
            if (resourceList.find(topicWords[k]) != resourceList.end())
            {
                resources.push_back(topicWords[k]);
            }
        }       
        
        for(int k=0; k < topicWords.size(); k++)
        {
            if (goalList.find(topicWords[k]) != goalList.end())
            {
                goals.push_back(topicWords[k]);
            }
        }       

        if (resources.size() != 0 || goals.size() != 0 )
        {
            TopicElements entry;
            entry.StoryTimeStart = storyInfoForTag[i].StoryTimeStart;
            entry.StoryTimeEnd = storyInfoForTag[i].StoryTimeEnd;
            entry.Resources = resources;
            entry.Goal = goals;
            resourceGoalTag.push_back(entry);
        }
    }
    return resourceGoalTag;
}

// input: StoryTagInfo.txt
vector<TopicElements> TextAnalysis::ReadTagFromFile1()
{
    string str, str2 ;
    vector<string> Person;
    vector<string> Location;
    
    vector<TopicElements> storyTagInfo;
    TopicElements entry;
    ifstream ifs;
    ifs.open("StoryTagInfo.txt", ios::in);
    if (!ifs.is_open()) cout<<"FileName File NOT opened"<<endl;
    while (!ifs.eof() && ifs.good() )
    {
        char buffer[2048];
        ifs.getline(buffer, 2048);
        str = (buffer);

        auto found_story = str.find("<story>");
        auto found_start = str.find("<start>");
        auto found_end = str.find( "<end>");
        auto found_person = str.find("[PER");
        auto found_location = str.find("[LOC"); 
        //auto found6 = str.find("[ORG");
        //auto found7 = str.find("[MISC");

        if (found_story == 0)
        {
            str2= str.substr(7,str.size());
            entry.StoryTopicName = str2;
        }

        if (found_start == 0)
        {
            str2= str.substr(7,str.size()-8);
            entry.StoryTimeStart = str2;
        }

        if (found_person == 0)
        {
            str2= str.substr(5,(str.size()-8));
            Person.push_back(str2);
        }
        if (found_location == 0)
        {
            str2= str.substr(5,(str.size()-8));
            Location.push_back(str2);
        }

        if (found_end == 0)
        {
            str2= str.substr(5,str.size());
            entry.StoryTimeEnd = str2;
        
            if  (Person.size() != 0 || Location.size() != 0)
            { 
                entry.Person = Person;
                entry.Location = Location;
                storyTagInfo.push_back(entry);
                Person.clear();
                Location.clear();
            }
        }
    }
    ifs.close();
    return storyTagInfo;
}


vector<StorySentInfo> TextAnalysis::GetNumberOfStorySentence(const vector<Triplet>& storyWordInfo)
{
    ofstream inout ;
    inout.open ("StoryAndSenNumber.txt");   

    vector<StorySentInfo> storyNameAndSenNum;
    int Allstory=0;

    for( int i=0; i < storyWordInfo.size(); i++)
    {
        size_t found , Found6_end = 1;
        found = storyWordInfo[i].StoryTopicName.find("<story>");
        if (found == 0)
        {
            int j = i;
            int NumOFSenInStory = 0;
            while ( Found6_end != 0 )
            {
                i++;
                NumOFSenInStory++;
                Found6_end = storyWordInfo[i].StoryTimeEnd.find("<end>");
            }
            string StoryName = storyWordInfo[j].StoryTopicName;

            StorySentInfo Info;
            Info.NameOFStoryTopic = (StoryName.substr(7, StoryName.size()));
            Info.NumOFSenInOneStory = (NumOFSenInStory-2);
            storyNameAndSenNum.push_back(Info);
            string TimeStart = storyWordInfo[j+1].StoryTimeStart;
            inout << TimeStart << "      " << Info.NameOFStoryTopic << "       " << Info.NumOFSenInOneStory << ","<< endl;
            
            Allstory = Allstory + NumOFSenInStory - 2;
        }
    }
    inout.close();
    return storyNameAndSenNum;
}

vector<Triplet> TextAnalysis::RemoveShortStory(const vector<Triplet>& storyWordInfo , 
    vector<int> & removedStories)
{   
    vector<Triplet> allStories;
    vector<Triplet> longStories;
    int j=0, num_stories = 0;
    for( int i=0; i < storyWordInfo.size(); i++)
    {
        size_t found, found_end = 1;
        found = storyWordInfo[i].StoryTopicName.find("<story>");
        j = i;
        if (found == 0)
        {
            num_stories ++;
            int NumOFSenInStory = 0;
            while ( found_end != 0 )
            {
                j++;
                NumOFSenInStory++;
                found_end = storyWordInfo[j].StoryTimeEnd.find("<end>");
            }
            
            if ( NumOFSenInStory-2 > 4)
            { // chose stories with more than 4 sentence
                j = i;
                found_end = 1;
                while ( found_end != 0 ) {
                    longStories.push_back( storyWordInfo[j]);
                    allStories.push_back( storyWordInfo[j]);
                    j++;
                    found_end = storyWordInfo[j].StoryTimeEnd.find("<end>");
                }
                longStories.push_back( storyWordInfo[j]);
            }
            else
            {
                removedStories.push_back(num_stories - 1);
                allStories.push_back(storyWordInfo[j]);
            }
        }
    }
    return longStories;
}

void TextAnalysis::ExtractVocabularyList(const vector<FinalTriplet>& storyWordInfoFinal,
    set<string>& vocabularyNP1, set<string>& vocabularyVP, set<string>& vocabularyNP2)
{
    vector<string> words, words1, words2;
    cout << storyWordInfoFinal.size() << endl;
    for(int i=0; i < storyWordInfoFinal.size(); i++)
    {
        istringstream iss(storyWordInfoFinal[i].Non_Ph1);
        copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));

        istringstream iss1(storyWordInfoFinal[i].Verb_Ph);
        copy (istream_iterator<string>(iss1), istream_iterator<string>(), back_inserter(words1));

        istringstream iss2(storyWordInfoFinal[i].Non_Ph2);
        copy (istream_iterator<string>(iss2), istream_iterator<string>(), back_inserter(words2));

        for (int j=0; j < words.size(); j++)
        {
            vocabularyNP1.insert(words[j]);
        }
        for (int j=0; j < words1.size(); j++)
        {
            vocabularyVP.insert(words1[j]);
        }
        for (int j=0; j < words2.size(); j++)
        {
            vocabularyNP2.insert(words2[j]);
        }

        words.clear();
        words1.clear();
        words2.clear();
    }   
}

void TextAnalysis::ParameterLearning(const vector<FinalTriplet> & storyWordInfo,
    const vector<StorySentInfo> & StoryNameAndSenNum,
    const set<string>& vocabularyNP1, 
    const set<string>& vocabularyVP, 
    const set<string>& vocabularyNP2)
    /*ring list_file10, string list_file11, string list_file12)*/
{   
    vector<FinalTriplet> storyWordInfoFinal = storyWordInfo;
    double B = factorial(100);
    ParameterOfModel Info;
    Info.Mu = 0;
    Info.prob_cat = 0;
    Info.prob_StoryGivenCat = 0;
    Info.Sigma = 0;
    //ModelParameter.push_back(Info);  
    //ModelParameter.clear();


    string str , str1 , str2 ;
    size_t found , found1 ;
    vector<string> labels_training , labels_testing;
    ofstream fout_eval;
    fout_eval.open("output/Triplets_CrossValidation.txt");

    vector<FinalTriplet> storyWordInfoFinalForTest, storyWordInfoFinalForTrain , storyWordInfoFinalOrg;
    int TrainSet=0 , TestSet=0, CountForTrainSet=0 , TotalSt=0;
    int AllStory = StoryNameAndSenNum.size();
    vector<int> TestPeriod;
    TestPeriod.push_back(0);
    TestSet = AllStory/10 +1;
    TrainSet = AllStory - TestSet;
    vector<double> crossValidation;
    for( int i=0; i < storyWordInfoFinal.size(); i++)
    {
        storyWordInfoFinalOrg.push_back(storyWordInfoFinal[i]);
    }

    for( int i=0; i < StoryNameAndSenNum.size(); i++)
    {

        for ( int Iindex=0+i; Iindex < TestSet + i; Iindex++ )
        {
            if(Iindex < StoryNameAndSenNum.size())
            {
                TotalSt = TotalSt + StoryNameAndSenNum[Iindex].NumOFSenInOneStory;      
            }
        }
        TestPeriod.push_back(TotalSt);
        i=i+TestSet-1;
    }
    fout_eval << "Number of Stories  in All Documents" << "      "  << StoryNameAndSenNum.size() << endl;

    for (int kk=0; kk<TestPeriod.size()-1; kk++)
    {
        storyWordInfoFinalForTest.clear();
        storyWordInfoFinalForTrain.clear();

        for (int i=0; i<storyWordInfoFinalOrg.size(); i++)
        {
            if(TestPeriod[kk] <= i &&  i < TestPeriod[kk+1])
            {
                storyWordInfoFinalForTest.push_back(storyWordInfoFinalOrg[i]);
            }
            else
            {
                storyWordInfoFinalForTrain.push_back(storyWordInfoFinalOrg[i]);
            }
        }

        labels_training.clear();
        for( int i=0; i < storyWordInfoFinalForTrain.size(); i++)
        {           
            if (storyWordInfoFinalForTrain[i].StoryTripletsCount == 0)
            {       
                string str = storyWordInfoFinalForTrain[i].StoryName;
                found1 = str.find('|' );
                str1 = str.substr ( 0, found1 );
                found = str1.find(':' );
                if (found < 50 ){
                    str1 = str1.substr ( 0, found );}
                if (str1 != "NULL" ){
                    labels_training.push_back(str1);}
            }
        }
        labels_testing.clear();
        for( int i=0; i < storyWordInfoFinalForTest.size(); i++)
        {   
            if (storyWordInfoFinalForTest[i].StoryTripletsCount == 0)
            {
                string str = storyWordInfoFinalForTest[i].StoryName;
                found1 = str.find('|' );
                str1 = str.substr ( 0, found1 );
                found = str1.find(':' );
                if (found < 50 )
                {
                    str1 = str1.substr ( 0, found );
                }
                if (str1 != "NULL" )
                {
                    labels_testing.push_back(str1);
                }
            }
        }
        storyWordInfoFinal.clear();
        for( int i=0; i < storyWordInfoFinalForTrain.size(); i++){  
            storyWordInfoFinal.push_back(storyWordInfoFinalForTrain[i]);
        }

        //"Weather","Activism",
        const char* array[] = {"War","Sports", "Disaster" , "Accident","Activism", "Weather",
            "Social","Government","Science-technology","Religion","Politics", "International" ,
            "Lifestyle-leisure" , "Labor" , "Human-interest" , "Health" , "Environment" , 
            "Education" , "Business" ,  "Money" , "Crime", "Justice", "Art-culture", "Celebrity",
            "Entertainment", "Network" , "Commercial"};
        vector<string> CategoryList(array, array + sizeof array / sizeof array[0]);
        vector<int> ProbCat;
        vector<double> prob_cat;
        int NumberOfStory = 0;


        for(int i=0; i < CategoryList.size(); i++){
            int Count = 0;
            for (int j=0; j < labels_training.size(); j++){
                if (CategoryList[i].compare(labels_training[j]) == 0){
                    Count++;
                }
            }
            ProbCat.push_back(Count);
            NumberOfStory = NumberOfStory + Count;
        }   

        if (NumberOfStory != labels_training.size()){
            cout<< " Error: Additional Category in Story list which NOT in The Main Category List"<< endl;
        }

        double ProbEachCat=0 , SmallNum =  1.5e-100;
        for(int i = 0; i < ProbCat.size(); i++){
            ProbEachCat = ProbCat[i];
            ProbEachCat = ProbEachCat/NumberOfStory;
            prob_cat.push_back(ProbEachCat);
        }

        //Creating co occurence of (words given cat) AND (words Given Stories) AND P(Wi | Catj)
        vector <double> EachCatInfo;
        vector<vector <double> > WordsCatMatrixNP1;
        vector<vector <double> > WordsStoriesMatrixNP1;
        vector<vector <double> > prob_wordsGivenCatsNP1;
        vector<vector <double> > WordsCatMatrixVP;
        vector<vector <double> > WordsStoriesMatrixVP;
        vector<vector <double> > prob_wordsGivenCatsVP;
        vector<vector <double> > WordsCatMatrixNP2;
        vector<vector <double> > WordsStoriesMatrixNP2;
        vector<vector <double> > prob_wordsGivenCatsNP2;
        

        // Building co occurence of (words given cat) AND (words Given Stories) AND P(Wi | Catj)
        for(int i=0; i < CategoryList.size(); i++){ 
            EachCatInfo.push_back(0);}
        for(int i=0; i < vocabularyNP1.size(); i++){    
            WordsCatMatrixNP1.push_back(EachCatInfo);
            prob_wordsGivenCatsNP1.push_back(EachCatInfo);}

        for(int i=0; i < vocabularyVP.size(); i++){
            WordsCatMatrixVP.push_back(EachCatInfo);
            prob_wordsGivenCatsVP.push_back(EachCatInfo);}

        for(int i=0; i < vocabularyNP2.size(); i++){
            WordsCatMatrixNP2.push_back(EachCatInfo);
            prob_wordsGivenCatsNP2.push_back(EachCatInfo);}


        EachCatInfo.clear();

        for(int i=0; i < NumberOfStory; i++){ 
            EachCatInfo.push_back(0);}
        for(int i=0; i < vocabularyNP1.size(); i++){    
            WordsStoriesMatrixNP1.push_back(EachCatInfo);}
        for(int i=0; i < vocabularyVP.size(); i++){ 
            WordsStoriesMatrixVP.push_back(EachCatInfo);}
        for(int i=0; i < vocabularyNP2.size(); i++){ 
            WordsStoriesMatrixNP2.push_back(EachCatInfo);}

        // for testing of correctness
        vector<WordCatInfo> WordCatInf;
        vector<WordCatInfo> WordCatInf1;
        vector<WordCatInfo> WordCatInf2;
        WordCatInfo WCInfo;

        ////vector<string> AllcountableWords;


        int NumberOfAllWordsInDocument=0;

        // Building  P(Si | Catj) AND P(Catj | Si)
        vector <double> CatInfor;
        vector<vector <double> > ProbStoryGivenCat;
        vector<vector <double> > ProbStoryGivenCat1;
        vector<vector <double> > ProbStoryGivenCat2;

        vector<vector <double> > ProbCatGivenStory;
        vector<vector <double> > ProbCatGivenStory1;
        vector<vector <double> > ProbCatGivenStory2;

        int CatInform = 0;
        for(int i=0; i < CategoryList.size(); i++)
        { 
            CatInfor.push_back(CatInform);
        }
        for(int i=0; i < NumberOfStory; i++)
        {
            ProbStoryGivenCat.push_back(CatInfor);
            ProbStoryGivenCat1.push_back(CatInfor);
            ProbStoryGivenCat2.push_back(CatInfor);

            ProbCatGivenStory.push_back(CatInfor);
            ProbCatGivenStory1.push_back(CatInfor);
            ProbCatGivenStory2.push_back(CatInfor);
        }

        vector<string> v(vocabularyNP1.begin(), vocabularyNP1.end());
        vector<string> v1(vocabularyVP.begin(), vocabularyVP.end());
        vector<string> v2(vocabularyNP2.begin(), vocabularyNP2.end());

        sort(v.begin(), v.end());
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());

        vector<string>::iterator low;
        vector<string>::iterator low1;
        vector<string>::iterator low2;

        vector<double> StoriesTime;
        vector<double> StoriesTime1;
        vector<double> StoriesTime2;

        vector<int> StoriesNum;
        vector<int> StoriesNum1;
        vector<int> StoriesNum2;

        int TotalNumOfWordsInDocs=0;
        int TotalNumOfWordsInDocs1=0;
        int TotalNumOfWordsInDocs2=0;


        sort (v.begin(), v.end());
        sort (v1.begin(), v1.end());
        sort (v2.begin(), v2.end());

        // Non_Ph1
        int Counter = 0 , CountOFStories = 0;
        for(int i=0; i < storyWordInfoFinal.size(); i++){
            int indicater = storyWordInfoFinal[i].StoryNUmber;
            if (storyWordInfoFinal[i].StoryTripletsCount == 0){
                StoriesTime.push_back(indicater);
                string str = storyWordInfoFinal[i].StoryName;
                found1 = str.find('|' );
                str1 = str.substr ( 0, found1 );
                found = str1.find(':' );
                if (found < 50 ){
                str1 = str1.substr ( 0, found );}
                if (str1.compare("NULL") != 0){
                    int storyCount = 0, NumOfWordsInEachStory = 0;
                    int Counter3 = i;
                    istringstream iss;
                    while ( storyCount < indicater ) {
                        storyCount++;
                        vector<string> words;
                        istringstream iss(storyWordInfoFinal[Counter3].Non_Ph1);
                        copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
                
                        for(int jj=0; jj < CategoryList.size(); jj++){
                            if (str1.compare(CategoryList[jj]) == 0){
                                for(int kk=0; kk < words.size(); kk++){
                                    low = lower_bound (v.begin(), v.end(), words[kk]);
                                    string WordName = *low;
                                    int wordPlace = int(low- v.begin());
                                    //cout << "position   " << wordPlace << "  "<<WordName<< "   " << CountOFStories<<"    "<< jj <<endl;
                                    if (wordPlace < vocabularyNP1.size() ){
                                        WordsCatMatrixNP1[wordPlace][jj] = 1+WordsCatMatrixNP1[wordPlace][jj];
                                        WordsStoriesMatrixNP1[wordPlace][CountOFStories] = 1+WordsStoriesMatrixNP1[wordPlace][CountOFStories];
                                        TotalNumOfWordsInDocs++;
                                        NumOfWordsInEachStory++;
                                    }
                                }
                            }
                        }
                        Counter3++;
                    }
                    CountOFStories++;
                        StoriesNum.push_back(NumOfWordsInEachStory);
                }
            }

            if (i==5847){
                int test = 9;
            }
        }

        // Verb_Ph

        Counter = 0 ; CountOFStories = 0;
        for(int i=0; i < storyWordInfoFinal.size(); i++){
            int indicater = storyWordInfoFinal[i].StoryNUmber;
            if (storyWordInfoFinal[i].StoryTripletsCount == 0){
                StoriesTime1.push_back(indicater);
                string str = storyWordInfoFinal[i].StoryName;
                found1 = str.find('|' );
                str1 = str.substr ( 0, found1 );
                found = str1.find(':' );
                if (found < 50 ){
                str1 = str1.substr ( 0, found );}
                if (str1.compare("NULL") != 0){
                    int storyCount = 0, NumOfWordsInEachStory1 = 0;
                    int Counter3 = i;
                    istringstream iss;
                    while ( storyCount < indicater ) {

                    storyCount++;
                    vector<string> words;

                    istringstream iss(storyWordInfoFinal[Counter3].Verb_Ph);
                    copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
                            
                        for(int jj=0; jj < CategoryList.size(); jj++){
                            if (str1.compare(CategoryList[jj]) == 0){
                                for(int kk=0; kk < words.size(); kk++){
                                    low = lower_bound (v1.begin(), v1.end(), words[kk]);
                                    string WordName = *low;
                                    int wordPlace = int(low- v1.begin());
                                    //cout << "position   " << wordPlace << "  "<<WordName<< "   " << CountOFStories<<"    "<< jj <<endl;
                                    if (wordPlace < vocabularyVP.size() ){
                                        WordsCatMatrixVP[wordPlace][jj] = 1+WordsCatMatrixVP[wordPlace][jj];
                                        WordsStoriesMatrixVP[wordPlace][CountOFStories] = 1+WordsStoriesMatrixVP[wordPlace][CountOFStories];
                                        TotalNumOfWordsInDocs1++;
                                        NumOfWordsInEachStory1++;
                                    }
                                }
                            }
                        }
                        Counter3++;
                    }
                    CountOFStories++;
                        StoriesNum1.push_back(NumOfWordsInEachStory1);
                }
            }
        }

        // Non_Ph2
        Counter = 0 ; CountOFStories = 0;
        for(int i=0; i < storyWordInfoFinal.size(); i++){
            int indicater = storyWordInfoFinal[i].StoryNUmber;
            if (storyWordInfoFinal[i].StoryTripletsCount == 0){
                StoriesTime2.push_back(indicater);
                string str = storyWordInfoFinal[i].StoryName;
                found1 = str.find('|' );
                str1 = str.substr ( 0, found1 );
                found = str1.find(':' );
                if (found < 50 ){
                str1 = str1.substr ( 0, found );}
                if (str1.compare("NULL") != 0){
                    int storyCount = 0, NumOfWordsInEachStory2 = 0;
                    int Counter3 = i;
                    istringstream iss;
                    while ( storyCount < indicater ) {

                    storyCount++;
                    vector<string> words;

                    istringstream iss(storyWordInfoFinal[Counter3].Non_Ph2);
                    copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
                            
                        for (int jj=0; jj < CategoryList.size(); jj++){
                            if (str1.compare(CategoryList[jj]) == 0){
                                for(int kk=0; kk < words.size(); kk++){
                                    low = lower_bound (v2.begin(), v2.end(), words[kk]);
                                    string WordName = *low;
                                    int wordPlace = int(low- v2.begin());
                                    //cout << "position   " << wordPlace << "  "<<WordName<< "   " << CountOFStories<<"    "<< jj <<endl;
                                    if (wordPlace < vocabularyNP2.size() ){
                                        WordsCatMatrixNP2[wordPlace][jj] = 1+WordsCatMatrixNP2[wordPlace][jj];
                                        WordsStoriesMatrixNP2[wordPlace][CountOFStories] = 1+WordsStoriesMatrixNP2[wordPlace][CountOFStories];
                                        TotalNumOfWordsInDocs2++;
                                        NumOfWordsInEachStory2++;
                                    }
                                }
                            }  
                        }
                        Counter3++;
                    }
                    CountOFStories++;
                    StoriesNum2.push_back(NumOfWordsInEachStory2);
                }
            }
        }


        vector<double> prob_storylen;
        vector<double> prob_storylen1;
        vector<double> prob_storylen2;

        for (int i=0; i< StoriesNum.size(); i++ ){
            double NumOfEqualStory=0;
            for (int j=0; j< StoriesNum.size(); j++ ){
                if (StoriesNum[i] == StoriesNum[j]){
                    NumOfEqualStory = NumOfEqualStory+1;
                }
            }
            double StoryProb = NumOfEqualStory/StoriesNum.size();
            prob_storylen.push_back(StoryProb);
        }

        for (int i=0; i< StoriesNum1.size(); i++ ){
            double NumOfEqualStory=0;
            for (int j=0; j< StoriesNum1.size(); j++ ){
                if (StoriesNum[i] == StoriesNum[j]){
                    NumOfEqualStory = NumOfEqualStory+1;
                }
            }
            double StoryProb = NumOfEqualStory/StoriesNum1.size();
            prob_storylen1.push_back(StoryProb);
        }

        for (int i=0; i< StoriesNum2.size(); i++ ){
            double NumOfEqualStory=0;
            for (int j=0; j< StoriesNum2.size(); j++ ){
                if (StoriesNum2[i] == StoriesNum2[j]){
                    NumOfEqualStory = NumOfEqualStory+1;
                }
            }
            double StoryProb = NumOfEqualStory/StoriesNum2.size();
            prob_storylen2.push_back(StoryProb);
        }

        // Calculating P(Wi|Catj)^time (Np1,Vp.Np2) and save it in WordsCatMatrixNP1,WordsCatMatrixVP,WordsCatMatrixNP2 

        for (int i=0; i< CategoryList.size(); i++ ){
            double NormFact=0 ;
            for (int j=0; j<vocabularyNP1.size(); j++){
                NormFact = NormFact + WordsCatMatrixNP1[j][i];}
            for (int j=0; j<vocabularyNP1.size(); j++){
                if (WordsCatMatrixNP1[j][i] != 0 && NormFact != 0 ){
                prob_wordsGivenCatsNP1[j][i] = WordsCatMatrixNP1[j][i]/NormFact;}
            }
        }

        for (int i=0; i< CategoryList.size(); i++ ){
            double NormFact=0 ;
            for (int j=0; j<vocabularyVP.size(); j++){
                NormFact = NormFact + WordsCatMatrixVP[j][i];}
            for (int j=0; j<vocabularyVP.size(); j++){
                if (WordsCatMatrixVP[j][i] != 0 && NormFact != 0 ){
                prob_wordsGivenCatsVP[j][i] = WordsCatMatrixVP[j][i]/NormFact;}
            }
        }

        for (int i=0; i< CategoryList.size(); i++ ){
            double NormFact=0 ;
            for (int j=0; j<vocabularyNP2.size(); j++){
                NormFact = NormFact + WordsCatMatrixNP2[j][i];}
            for (int j=0; j<vocabularyNP2.size(); j++){
                if (WordsCatMatrixNP2[j][i] != 0 && NormFact != 0 ){
                prob_wordsGivenCatsNP2[j][i] = WordsCatMatrixNP2[j][i]/NormFact;}
            }
        }

        //Building The Probability of Story Given Category  P(Si|Catj)^time  for NP1,VP,NP2

        vector<int> AllCountedWordsInStories;
        vector<int> AllCountedWordsInStories1;
        vector<int> AllCountedWordsInStories2;


            Counter = 0; int Counter1= 0;
            for(int i=0; i < storyWordInfoFinal.size(); i++){
                int indicater = storyWordInfoFinal[i].StoryNUmber;
                if (storyWordInfoFinal[i].StoryTripletsCount <= 0){
                
                    string str = storyWordInfoFinal[i].StoryName;
                    found1 = str.find('|' );
                    str1 = str.substr ( 0, found1 );
                    found = str1.find(':' );
                    if (found < 50 ){
                    str1 = str1.substr ( 0, found );}
                    if (Counter1 < ProbStoryGivenCat.size()){
                    if (str1.compare("NULL") != 0){
                        int storyCount = 0; 
                        vector<double> prob_EntitiesinOneStorygivnCat;
                        vector<int> FrequencyOfEachWord;
                        prob_EntitiesinOneStorygivnCat.clear();
                        int jjj = 0;    
                        for(int jj=0; jj < CategoryList.size(); jj++){
                            if (str1.compare(CategoryList[jj]) == 0){
                                jjj = jj;}
                        }
                        istringstream iss;
                        int Counter2 = i, NumOFWordInOneStory=0, NumOfEntities=0;
                        while ( storyCount < indicater ) {
                    
                            storyCount++;
                            vector<string> words;   
                            istringstream iss(storyWordInfoFinal[Counter2].Non_Ph1);
                            copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
                            for(int kk=0; kk < words.size(); kk++){
                            low = lower_bound (v.begin(), v.end(), words[kk]);
                            double prob_EntitygivnCat = 0;
                                string WordName = *low;             
                                    if(WordName.compare(words[kk]) == 0){
                                        int wordPlace = int(low- v.begin());
                                        //cout << "My Search   " << wordPlace << " "<<jjj<<"  "<<WordName<<"  "<<Counter++ <<endl;              
                                        double NumOfEntity=0 , fact=0, prob_Entity=0;
                                        if (wordPlace < vocabularyNP1.size() ){
                                            WCInfo.word = WordName;
                                            WCInfo.Cat = CategoryList[jjj];
                                            WCInfo.StNumInList = Counter1;
                                            WCInfo.wordPlaceInDic = wordPlace;
                                            WordCatInf.push_back(WCInfo);
                                            //if(Counter == 551){
                                            //  int test = 0;
                                            //}
                                            //  AllcountableWords.push_back(WordName);
                                            NumOfEntity = WordsCatMatrixNP1[wordPlace][jjj];
                                            prob_Entity = prob_wordsGivenCatsNP1[wordPlace][jjj];
                                            NumOfEntities = NumOfEntities + NumOfEntity;
                                            NumOFWordInOneStory++;
                                            //prob_EntitygivnCat = NumOfEntity/TotalNumOfWordsInDocs;                       
                                        }
                                        FrequencyOfEachWord.push_back(NumOfEntity);
                                        prob_EntitiesinOneStorygivnCat.push_back(prob_Entity);
                                    }                       
                            }
                            Counter2++;
                        }

                        //unsigned __int64 NumOfWordFactorial = 0; //    // P(Si|Cj) = (n!/(W1!,W2!,...,Wk!)(P^W1*P^W2,....P^Wk)            
                        double prob_OneStorygivnCat = 1;
                        //double Numerator = 1;
                        //int DeNumerator = 1; 
                        //unsigned __int64 fact = 1;
                        //fact = factorial(NumOfEntities);
                        //NumOfWordFactorial = fact;
                        for (int kk = 0; kk < prob_EntitiesinOneStorygivnCat.size(); kk++){
                        //int Num = FrequencyOfEachWord[kk];
                        //Numerator = Numerator*pow ( prob_EntitiesinOneStorygivnCat[kk] , FrequencyOfEachWord[kk] );
                        //fact = factorial(Num);
                        //DeNumerator = DeNumerator*fact;
                        prob_OneStorygivnCat = prob_OneStorygivnCat * prob_EntitiesinOneStorygivnCat[kk];}
                        //prob_OneStorygivnCat = NumOfWordFactorial*Numerator/DeNumerator;
                        if (prob_OneStorygivnCat < SmallNum){
                        ProbStoryGivenCat[Counter1][jjj] = SmallNum;}else{
                            ProbStoryGivenCat[Counter1][jjj] = prob_OneStorygivnCat * prob_storylen[Counter1];}
                        //  prob_EntitygivnCatFull = prob_EntitygivnCatFull+prob_EntitiesinOneStorygivnCat[kk];
                        AllCountedWordsInStories.push_back(NumOFWordInOneStory);
                        //NumberOfAllWordsInDocument = NumberOfAllWordsInDocument+(prob_EntitiesinOneStorygivnCat.size());
                        //if (prob_EntitygivnCatFull != 0){// && prob_EntitygivnCatFull != 1){
                        //  ProbStoryGivenCat[Counter1][jjj] = prob_EntitygivnCatFull;///prob_EntitiesinOneStorygivnCat.size();
                        //}

                        Counter1++;
                    }
                }
                }
            }

            Counter = 0;  Counter1= 0;
            for(int i=0; i < storyWordInfoFinal.size(); i++){
                int indicater = storyWordInfoFinal[i].StoryNUmber;
                if (storyWordInfoFinal[i].StoryTripletsCount == 0){
                
                    string str = storyWordInfoFinal[i].StoryName;
                    found1 = str.find('|' );
                    str1 = str.substr ( 0, found1 );
                    found = str1.find(':' );
                    if (found < 50 ){
                    str1 = str1.substr ( 0, found );}
                if (Counter1 < ProbStoryGivenCat.size()){
                    if (str1.compare("NULL") != 0){
                        int storyCount = 0; 
                        vector<double> prob_EntitiesinOneStorygivnCat;
                        vector<int> FrequencyOfEachWord;
                        prob_EntitiesinOneStorygivnCat.clear();
                        int jjj = 0;    
                        for(int jj=0; jj < CategoryList.size(); jj++){
                            if (str1.compare(CategoryList[jj]) == 0){
                                jjj = jj;}
                        }
                        istringstream iss;
                        int Counter2 = i, NumOFWordInOneStory=0, NumOfEntities=0;
                        while ( storyCount < indicater ) {
                    
                            storyCount++;
                            vector<string> words;   
                            istringstream iss(storyWordInfoFinal[Counter2].Verb_Ph);
                            copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
                            for(int kk=0; kk < words.size(); kk++){
                                low = lower_bound (v1.begin(), v1.end(), words[kk]);
                                double prob_EntitygivnCat = 0;
                                string WordName = *low;             
                                if(WordName.compare(words[kk]) == 0){
                                    int wordPlace = int(low- v1.begin());
                                    //cout << "My Search   " << wordPlace << " "<<jjj<<"  "<<WordName<<"  "<<Counter++ <<endl;              
                                    double NumOfEntity=0 , fact=0, prob_Entity=0;
                                        if (wordPlace < vocabularyVP.size() ){
                                            WCInfo.word = WordName;
                                            WCInfo.Cat = CategoryList[jjj];
                                            WCInfo.StNumInList = Counter1;
                                            WCInfo.wordPlaceInDic = wordPlace;
                                            WordCatInf1.push_back(WCInfo);

                                            NumOfEntity = WordsCatMatrixVP[wordPlace][jjj];
                                            prob_Entity = prob_wordsGivenCatsVP[wordPlace][jjj];
                                            NumOfEntities = NumOfEntities + NumOfEntity;
                                            NumOFWordInOneStory++;
                                            //prob_EntitygivnCat = NumOfEntity/TotalNumOfWordsInDocs;                       
                                        }
                                    FrequencyOfEachWord.push_back(NumOfEntity);
                                    prob_EntitiesinOneStorygivnCat.push_back(prob_Entity);
                                }                   
                            }
                            Counter2++;
                        }

                        //unsigned __int64 NumOfWordFactorial = 0; //    // P(Si|Cj) = (n!/(W1!,W2!,...,Wk!)(P^W1*P^W2,....P^Wk)            
                        double prob_OneStorygivnCat = 1;
                        for (int kk = 0; kk < prob_EntitiesinOneStorygivnCat.size(); kk++){
                        prob_OneStorygivnCat = prob_OneStorygivnCat * prob_EntitiesinOneStorygivnCat[kk];}
                        if (prob_OneStorygivnCat < SmallNum){
                        ProbStoryGivenCat1[Counter1][jjj] = SmallNum;}else{
                            ProbStoryGivenCat1[Counter1][jjj] = prob_OneStorygivnCat * prob_storylen[Counter1];}
                        AllCountedWordsInStories1.push_back(NumOFWordInOneStory);
                        Counter1++;
                    }
                }
                }
            }

            Counter = 0; Counter1= 0;
            for(int i=0; i < storyWordInfoFinal.size(); i++){
                int indicater = storyWordInfoFinal[i].StoryNUmber;
                if (storyWordInfoFinal[i].StoryTripletsCount == 0){
                
                    string str = storyWordInfoFinal[i].StoryName;
                    found1 = str.find('|' );
                    str1 = str.substr ( 0, found1 );
                    found = str1.find(':' );
                    if (found < 50 ){
                    str1 = str1.substr ( 0, found );}
                if (Counter1 < ProbStoryGivenCat.size()){
                    if (str1.compare("NULL") != 0){
                        int storyCount = 0; 
                        vector<double> prob_EntitiesinOneStorygivnCat;
                        vector<int> FrequencyOfEachWord;
                        prob_EntitiesinOneStorygivnCat.clear();
                        int jjj = 0;    
                        for(int jj=0; jj < CategoryList.size(); jj++){
                            if (str1.compare(CategoryList[jj]) == 0){
                                jjj = jj;}
                        }
                        istringstream iss;
                        int Counter2 = i, NumOFWordInOneStory=0, NumOfEntities=0;
                        while ( storyCount < indicater ) {
                    
                            storyCount++;
                            vector<string> words;   
                            istringstream iss(storyWordInfoFinal[Counter2].Non_Ph2);
                            copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
                            for(int kk=0; kk < words.size(); kk++){
                                low = lower_bound (v2.begin(), v2.end(), words[kk]);
                                double prob_EntitygivnCat = 0;
                                string WordName = *low;             
                                if(WordName.compare(words[kk]) == 0){
                                    int wordPlace = int(low- v2.begin());
                                    //cout << "My Search   " << wordPlace << " "<<jjj<<"  "<<WordName<<"  "<<Counter++ <<endl;              
                                    double NumOfEntity=0 , fact=0, prob_Entity=0;
                                        if (wordPlace < vocabularyNP2.size() ){
                                            WCInfo.word = WordName;
                                            WCInfo.Cat = CategoryList[jjj];
                                            WCInfo.StNumInList = Counter1;
                                            WCInfo.wordPlaceInDic = wordPlace;
                                            WordCatInf2.push_back(WCInfo);

                                            NumOfEntity = WordsCatMatrixNP2[wordPlace][jjj];
                                            prob_Entity = prob_wordsGivenCatsNP2[wordPlace][jjj];
                                            NumOfEntities = NumOfEntities + NumOfEntity;
                                            NumOFWordInOneStory++;
                                            //prob_EntitygivnCat = NumOfEntity/TotalNumOfWordsInDocs;                       
                                        }
                                    FrequencyOfEachWord.push_back(NumOfEntity);
                                    prob_EntitiesinOneStorygivnCat.push_back(prob_Entity);
                                }                       
                            }
                            Counter2++;
                        }

                        //unsigned __int64 NumOfWordFactorial = 0; //    // P(Si|Cj) = (n!/(W1!,W2!,...,Wk!)(P^W1*P^W2,....P^Wk)            
                        double prob_OneStorygivnCat = 1;
                        for (int kk = 0; kk < prob_EntitiesinOneStorygivnCat.size(); kk++){
                        prob_OneStorygivnCat = prob_OneStorygivnCat * prob_EntitiesinOneStorygivnCat[kk];
                        }
                        //cout<< "prob_OneStorygivnCat" <<"    "<< prob_OneStorygivnCat<<endl;
                        
                        if (prob_OneStorygivnCat < SmallNum ){
                        ProbStoryGivenCat2[Counter1][jjj] = SmallNum;
                        }else{
                            ProbStoryGivenCat2[Counter1][jjj] = prob_OneStorygivnCat * prob_storylen[Counter1];
                        }
                        AllCountedWordsInStories2.push_back(NumOFWordInOneStory);
        

                        Counter1++;
                    }
                }
                }
            }

        //Normolasation of the ProbStoryGivenCat which gives Probability of Story Given Category:P(Si|Catj)^time

        //for (int i=0; i<CategoryList.size(); i++){
        //  double NormFact=0;
        //  for (int j=0; j<NumberOfStory; j++){
        //      NormFact = NormFact+ProbStoryGivenCat[j][i];
        //  }
        //  if (NormFact != 0){
        //  for (int j=0; j<NumberOfStory; j++){
        //      ProbStoryGivenCat[j][i] = ProbStoryGivenCat[j][i]/NormFact;}
        //  }
        //}


        for (int i=0; i<CategoryList.size(); i++){
            double NormFact=0;
            for (int j=0; j<NumberOfStory; j++){
                NormFact = NormFact + ProbStoryGivenCat[j][i];}
            for (int j=0; j<NumberOfStory; j++){
                if (NormFact != 0 && ProbStoryGivenCat[j][i] != 0){
                    ProbStoryGivenCat[j][i] = ProbStoryGivenCat[j][i]/NormFact;}}}

        for (int i=0; i<CategoryList.size(); i++){
            double NormFact=0;
            for (int j=0; j<NumberOfStory; j++){
                NormFact = NormFact + ProbStoryGivenCat1[j][i];}
            for (int j=0; j<NumberOfStory; j++){
                if (NormFact != 0 && ProbStoryGivenCat1[j][i] != 0){
                    ProbStoryGivenCat1[j][i] = ProbStoryGivenCat1[j][i]/NormFact;}}}

        for (int i=0; i<CategoryList.size(); i++){
            double NormFact=0;
            for (int j=0; j<NumberOfStory; j++){
                NormFact = NormFact + ProbStoryGivenCat2[j][i];}
            for (int j=0; j<NumberOfStory; j++){
                if (NormFact != 0 && ProbStoryGivenCat2[j][i] != 0){
                    ProbStoryGivenCat2[j][i] = ProbStoryGivenCat2[j][i]/NormFact;}}}



        vector<double> prob_Story;
        vector<double> prob_Story1;
        vector<double> prob_Story2;

        for (int i=0; i<NumberOfStory; i++){
            double NormFact=0;
            for (int j=0; j<CategoryList.size(); j++){
                NormFact = NormFact + prob_cat[j]*ProbStoryGivenCat[i][j];}
                prob_Story.push_back(NormFact);}
        for (int i=0; i<NumberOfStory; i++){
            double NormFact=0;
            for (int j=0; j<CategoryList.size(); j++){
                NormFact = NormFact + prob_cat[j]*ProbStoryGivenCat1[i][j];}
                prob_Story1.push_back(NormFact);}
        for (int i=0; i<NumberOfStory; i++){
            double NormFact=0;
            for (int j=0; j<CategoryList.size(); j++){
                NormFact = NormFact + prob_cat[j]*ProbStoryGivenCat2[i][j];}
                prob_Story2.push_back(NormFact);}
    ///       Starting Iteration for EM - Algorithm


    // E_Step: 
    //Building The Probability  of Category Given Story P(Catj|Si)^(t+1)   t=time  FOR NP1,VP,NP2

        for (int i=0; i<NumberOfStory; i++){
            for (int j=0; j<CategoryList.size(); j++){
                ProbCatGivenStory[i][j] = prob_cat[j]*ProbStoryGivenCat[i][j]/prob_Story[i];
            }
        }
        for (int i=0; i<NumberOfStory; i++){
            for (int j=0; j<CategoryList.size(); j++){
                ProbCatGivenStory1[i][j] = prob_cat[j]*ProbStoryGivenCat1[i][j]/prob_Story1[i];
            }
        }
        for (int i=0; i<NumberOfStory; i++){
            for (int j=0; j<CategoryList.size(); j++){
                ProbCatGivenStory2[i][j] = prob_cat[j]*ProbStoryGivenCat2[i][j]/prob_Story2[i];
            }
        }

    //Normolasation of the ProbCatGivenStory which is Probability of Category Given Story:P(Catj|Si)^time+1

        //for (int i=0; i<CategoryList.size(); i++){
        //  double NormFact=0;
        //  for (int j=0; j<NumberOfStory; j++){
        //      NormFact = NormFact+ProbCatGivenStory[j][i];
        //  }
        //  if (NormFact != 0){
        //  for (int j=0; j<NumberOfStory; j++){
        //      ProbCatGivenStory[j][i] = ProbCatGivenStory[j][i]/NormFact;}
        //  }
        //}

    // M_Step: 
    // Updating The Probability  of Each Words in vocabulars Given Category    
    // P(Wn|Catj)^(t+1)   t=time

        for (int i=0; i<vocabularyNP1.size(); i++){
            for (int j=0; j<CategoryList.size(); j++){
                double Numeratorwithoutsmooth = 0;
                double DeNumeratorwithoutsmooth = 0;
                for (int k=0; k<NumberOfStory; k++){
                Numeratorwithoutsmooth = Numeratorwithoutsmooth + ProbCatGivenStory[k][j]*WordsStoriesMatrixNP1[i][k];
                DeNumeratorwithoutsmooth  = DeNumeratorwithoutsmooth + ProbCatGivenStory[k][j]*AllCountedWordsInStories[k]; 
                }
                prob_wordsGivenCatsNP1[i][j] = (1 + Numeratorwithoutsmooth) / (vocabularyNP1.size() + DeNumeratorwithoutsmooth);
            }
        }

        for (int i=0; i<vocabularyVP.size(); i++){
            for (int j=0; j<CategoryList.size(); j++){
                double Numeratorwithoutsmooth = 0;
                double DeNumeratorwithoutsmooth = 0;
                for (int k=0; k<NumberOfStory; k++){
                Numeratorwithoutsmooth = Numeratorwithoutsmooth + ProbCatGivenStory1[k][j]*WordsStoriesMatrixVP[i][k];
                DeNumeratorwithoutsmooth  = DeNumeratorwithoutsmooth + ProbCatGivenStory1[k][j]*AllCountedWordsInStories[k];    
                }
                prob_wordsGivenCatsVP[i][j] = (1 + Numeratorwithoutsmooth) / (vocabularyVP.size() + DeNumeratorwithoutsmooth);
            }
        }

        for (int i=0; i<vocabularyNP2.size(); i++){
            for (int j=0; j<CategoryList.size(); j++){
                double Numeratorwithoutsmooth = 0;
                double DeNumeratorwithoutsmooth = 0;
                for (int k=0; k<NumberOfStory; k++){
                Numeratorwithoutsmooth = Numeratorwithoutsmooth + ProbCatGivenStory2[k][j]*WordsStoriesMatrixNP2[i][k];
                DeNumeratorwithoutsmooth  = DeNumeratorwithoutsmooth + ProbCatGivenStory2[k][j]*AllCountedWordsInStories[k];
                //cout<< "[k][j]" <<k<< "    "<<j<<   "      "<<DeNumeratorwithoutsmooth<<endl;
                }
                prob_wordsGivenCatsNP2[i][j] = (1 + Numeratorwithoutsmooth) / (vocabularyNP2.size() + DeNumeratorwithoutsmooth);
            }
        }

        // Inference : Find the Posterior of new Unknown Story
        int Pred=0;
        for ( int ii=0; ii<labels_testing.size(); ii++){
            //int randStory = (rand() % (labels_testing.size())); //labels_training
            string labeled_category = labels_testing[ii];  //labels_training  -  [randStory]

            vector<double> Posteriorprob_catGivenStoryNP1;
            vector<double> Posteriorprob_catGivenStoryVP;
            vector<double> Posteriorprob_catGivenStoryNP2;

        //Posteriorprob_catGivenStoryNP1
            for(int j=0; j < CategoryList.size(); j++){
                double Numerator=0 , DeNumerator=0, TotalProbWordsGivenCat=1;
                int CountToFindStory=0;
                for( int i=0; i < storyWordInfoFinalForTest.size(); i++){   
                    for (int jj=0; jj<storyWordInfoFinalForTest[i].StoryNUmber; jj++){
                        if( CountToFindStory == ii ){ //randStory
                            vector<string> words;
                            istringstream iss(storyWordInfoFinalForTest[jj+i].Non_Ph1);
                            copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
                            if (words.size() != 0){
                                for(int kk=0; kk < words.size(); kk++){
                                    low = lower_bound (v.begin(), v.end(), words[kk]);
                                    string WordName = *low;
                                    int wordPlace = int(low- v.begin());
                                    double B = prob_wordsGivenCatsNP1[wordPlace][j];
                                    TotalProbWordsGivenCat = TotalProbWordsGivenCat * B;
                                }
                            }
                        }
                    }

                CountToFindStory++;
                i= i+storyWordInfoFinalForTest[i].StoryNUmber-1;
                }
            Numerator = prob_cat[j] * TotalProbWordsGivenCat;
            Posteriorprob_catGivenStoryNP1.push_back(Numerator);}
            double NormFact=0;
            for (int j=0; j<Posteriorprob_catGivenStoryNP1.size(); j++){
                double A = Posteriorprob_catGivenStoryNP1[j];
                NormFact = NormFact + A;
            }
            for (int i=0; i<Posteriorprob_catGivenStoryNP1.size(); i++){
                Posteriorprob_catGivenStoryNP1[i] = Posteriorprob_catGivenStoryNP1[i]/NormFact;
            }

                                                                                            //////for(int j=0; j < CategoryList.size(); j++){
        //////double Numerator=0 , DeNumerator=0, TotalProbWordsGivenCat=1;
        //////  for (int k=0; k<WordCatInf.size(); k++){
        //////      if (WordCatInf[k].StNumInList == randStory){
        //////          double A = WordCatInf[k].wordPlaceInDic;//prob_storylen
        //////          double B = prob_wordsGivenCatsNP1[A][j];
        //////          TotalProbWordsGivenCat = TotalProbWordsGivenCat * B;
        //////      }
        //////  }
        //////  Numerator = prob_cat[j] * TotalProbWordsGivenCat;
        //////  Posteriorprob_catGivenStoryNP1.push_back(Numerator);
        //////}///DeNumerator);
        //////double NormFact=0;
        //////for (int j=0; j<Posteriorprob_catGivenStoryNP1.size(); j++){
        //////  double A = Posteriorprob_catGivenStoryNP1[j];
        //////  NormFact = NormFact + A;
        //////}
        //////for (int i=0; i<Posteriorprob_catGivenStoryNP1.size(); i++){
        //////  Posteriorprob_catGivenStoryNP1[i] = Posteriorprob_catGivenStoryNP1[i]/NormFact;
        //////}



    //Posteriorprob_catGivenStoryVP

            for(int j=0; j < CategoryList.size(); j++){
                double Numerator=0 , DeNumerator=0, TotalProbWordsGivenCat=1;
                int CountToFindStory=0;
                for( int i=0; i < storyWordInfoFinalForTest.size(); i++){   
                    for (int jj=0; jj<storyWordInfoFinalForTest[i].StoryNUmber; jj++){
                        if( CountToFindStory == ii ){ //randStory
                            vector<string> words;
                            istringstream iss(storyWordInfoFinalForTest[jj+i].Verb_Ph);
                            copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
                            if (words.size() != 0){
                                for(int kk=0; kk < words.size(); kk++){
                                    low = lower_bound (v1.begin(), v1.end(), words[kk]);
                                    string WordName = *low;
                                    int wordPlace = int(low- v1.begin());
                                    double B = prob_wordsGivenCatsVP[wordPlace][j];
                                    TotalProbWordsGivenCat = TotalProbWordsGivenCat * B;
                                }
                            }
                        }
                    }

                CountToFindStory++;
                i= i+storyWordInfoFinalForTest[i].StoryNUmber-1;
                }
            Numerator = prob_cat[j] * TotalProbWordsGivenCat;
            Posteriorprob_catGivenStoryVP.push_back(Numerator);}
            NormFact=0;
            for (int j=0; j<Posteriorprob_catGivenStoryVP.size(); j++){
                double A = Posteriorprob_catGivenStoryVP[j];
                NormFact = NormFact + A;
            }
            for (int i=0; i<Posteriorprob_catGivenStoryVP.size(); i++){
                Posteriorprob_catGivenStoryVP[i] = Posteriorprob_catGivenStoryVP[i]/NormFact;
            }
                                                                    //for(int j=0; j < CategoryList.size(); j++){
        //double Numerator=0 , DeNumerator=0, TotalProbWordsGivenCat=1;
        //  for (int k=0; k<WordCatInf1.size(); k++){
        //      if (WordCatInf1[k].StNumInList == randStory){
        //          double A = WordCatInf1[k].wordPlaceInDic;//prob_storylen
        //          double B = prob_wordsGivenCatsVP[A][j];
        //          TotalProbWordsGivenCat = TotalProbWordsGivenCat * B;}}
        //  Numerator = prob_cat[j] * TotalProbWordsGivenCat;
        //  Posteriorprob_catGivenStoryVP.push_back(Numerator);}///DeNumerator);
        //NormFact=0;
        //for (int j=0; j<Posteriorprob_catGivenStoryVP.size(); j++){
        //  double A = Posteriorprob_catGivenStoryVP[j];
        //  NormFact = NormFact + A;}
        //for (int i=0; i<Posteriorprob_catGivenStoryVP.size(); i++){
        //  Posteriorprob_catGivenStoryVP[i] = Posteriorprob_catGivenStoryVP[i]/NormFact;}

            for(int j=0; j < CategoryList.size(); j++){
                double Numerator=0 , DeNumerator=0, TotalProbWordsGivenCat=1;
                int CountToFindStory=0;
                for( int i=0; i < storyWordInfoFinalForTest.size(); i++){   
                    for (int jj=0; jj<storyWordInfoFinalForTest[i].StoryNUmber; jj++){
                        if( CountToFindStory == ii ){ //randStory
                            vector<string> words;
                            istringstream iss(storyWordInfoFinalForTest[jj+i].Non_Ph2);
                            copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
                            if (words.size() != 0){
                                for(int kk=0; kk < words.size(); kk++){
                                    low = lower_bound (v2.begin(), v2.end(), words[kk]);
                                    string WordName = *low;
                                    int wordPlace = int(low- v2.begin());
                                    double B = prob_wordsGivenCatsNP2[wordPlace][j];
                                    TotalProbWordsGivenCat = TotalProbWordsGivenCat * B;
                                }
                            }
                        }
                    }

                CountToFindStory++;
                i= i+storyWordInfoFinalForTest[i].StoryNUmber-1;
                }
            Numerator = prob_cat[j] * TotalProbWordsGivenCat;
            Posteriorprob_catGivenStoryNP2.push_back(Numerator);

            }///DeNumerator);
            NormFact=0;
            for (int j=0; j<Posteriorprob_catGivenStoryNP2.size(); j++){
                double A = Posteriorprob_catGivenStoryNP2[j];
                NormFact = NormFact + A;
            }
            for (int i=0; i<Posteriorprob_catGivenStoryNP2.size(); i++){
                Posteriorprob_catGivenStoryNP2[i] = Posteriorprob_catGivenStoryNP2[i]/NormFact;
            }

        //Posteriorprob_catGivenStoryNP2
        //for(int j=0; j < CategoryList.size(); j++){
        //double Numerator=0 , DeNumerator=0, TotalProbWordsGivenCat=1;
        //  for (int k=0; k<WordCatInf2.size(); k++){
        //      if (WordCatInf2[k].StNumInList == randStory){
        //          double A = WordCatInf2[k].wordPlaceInDic;//prob_storylen
        //          double B = prob_wordsGivenCatsNP2[A][j];
        //          TotalProbWordsGivenCat = TotalProbWordsGivenCat * B;}}
        //  Numerator = prob_cat[j] * TotalProbWordsGivenCat;
        //  Posteriorprob_catGivenStoryNP2.push_back(Numerator);}///DeNumerator);
        //NormFact=0;
        //for (int j=0; j<Posteriorprob_catGivenStoryNP2.size(); j++){
        //  double A = Posteriorprob_catGivenStoryNP2[j];
        //  NormFact = NormFact + A;}
        //for (int i=0; i<Posteriorprob_catGivenStoryNP2.size(); i++){
        //  Posteriorprob_catGivenStoryNP2[i] = Posteriorprob_catGivenStoryNP2[i]/NormFact;}

        
        //Total Posterior Probibility Of Cat Given Story
            vector<double> TotalPosteriorprob_catGivenStory;
            for (int i=0; i<Posteriorprob_catGivenStoryNP2.size(); i++){
                double A =  Posteriorprob_catGivenStoryNP1[i] * Posteriorprob_catGivenStoryVP[i] * Posteriorprob_catGivenStoryNP2[i];
                TotalPosteriorprob_catGivenStory.push_back(A);
            }

            double elems[NUM_CATEGORIES];
            copy(TotalPosteriorprob_catGivenStory.begin(), TotalPosteriorprob_catGivenStory.end(), elems);
            vector<double> myVector(elems, elems + TotalPosteriorprob_catGivenStory.size()); 
            vector<double>::const_iterator it2;  
                                    // Find the min and max elements in the vector
        //it2 = max_element(myVector.begin(), myVector.end());
        //cout << " the max is " << * (max_element(myVector.begin(), myVector.end()) ) << endl;
        //cout << "max value location at " << max_element(myVector.begin(), myVector.end()) - myVector.begin();
            string predicted_category = CategoryList[max_element(myVector.begin(), myVector.end()) - myVector.begin()];

            found = storyWordInfoFinalForTest[ii].StoryName.find("South-Ossetia");
            found1 = storyWordInfoFinalForTest[ii].StoryName.find("georgia");

            if ( predicted_category == labeled_category ){
                Pred = Pred +1; 
            }else{
                if( (predicted_category=="War" && found < 50) || labeled_category == "Human-interest" || 
                    predicted_category == "Human-interest" ||
                    (predicted_category=="Crime" && labeled_category == "Justice") || 
                    (predicted_category=="Justice" && labeled_category == "Crime") ||
                    (labeled_category=="International" && found < 50) || 
                    labeled_category=="Celebrity" || labeled_category=="Entertainment" ||
                    (predicted_category=="Weather" && labeled_category == "Disaster")|| 
                    (predicted_category=="Disaster" && labeled_category == "Weather") ||
                    (predicted_category=="Crime" && labeled_category == "Accident")|| (
                    predicted_category=="Accident" && labeled_category == "Crime")||
                    labeled_category=="Entertainment" || predicted_category=="Entertainment"||
                    (predicted_category=="War" && found1 < 10000) ){
                    Pred = Pred +1;
                    }
            }
        }

        crossValidation.push_back(double (double (Pred)/labels_testing.size()));
    }

    PrintCrossValidationReport(fout_eval, crossValidation);
    fout_eval.close();
}


vector<FinalTriplet> TextAnalysis::RemoveStopWords(
    const vector<Triplet> & storyWordInfo,
    const vector<StorySentInfo> & StoryNameAndSenNum)
{   
    vector<FinalTriplet> storyWordInfoFinal;
    ofstream inout ;
    ofstream inout1 ;
    size_t foundNP1, foundVP ;
    vector<string> Non_Ph1 , Verb_Ph , Non_Ph2 ;

    FinalTriplet entry; 

    int Count = 0;
    inout.open(FILE_ANNA_BEFORE_SPLIT);
    for(int i=0; i < storyWordInfo.size(); i++){
        if (storyWordInfo[i].StoryTimeEnd == "" && storyWordInfo[i].StoryTimeStart == ""
            && storyWordInfo[i].StoryTopicName == "" ){
            Count++;
            if (storyWordInfo[i].Non_Ph1 == ""){ 
                inout << "this" << endl; // add stop word to empty line
            }else{
                inout << storyWordInfo[i].Non_Ph1 << endl;
            }
        }
    }
    inout.close();

    string CMD_split = "java -cp " FILE_ANNA_JAR " is2.util.Split " FILE_ANNA_BEFORE_SPLIT " > " FILE_ANNA_AFTER_SPLIT;
    system(CMD_split.c_str());

    string CMD_lemmatize = "java -Xmx2G -cp " FILE_ANNA_JAR " is2.lemmatizer.Lemmatizer -model " FILE_LEMMA_ENG_MODEL " -test " FILE_ANNA_AFTER_SPLIT " -out Lemmatizedfile.txt";
    system(CMD_lemmatize.c_str());

    ifstream lemmed ("Lemmatizedfile.txt");
    char buffer[500];
    char * pch;
    vector<string> lemmatized_words;
    string wholeString , str_buf , str12 , str ;                        
    ofstream lemm_words ;
    lemm_words.open ("lemmatized_words.txt");

    while (!lemmed.eof() && lemmed.good() ) {
        lemmed.getline(buffer, 500, '\n');
        str_buf = (buffer);

        if (str_buf == "") {
            lemmatized_words.push_back(wholeString);
            lemm_words << wholeString << '\n';
            Non_Ph1.push_back(wholeString);
            //entry.Non_Ph1 = wholeString;
            //FinalTriplet.push_back(entry);
            wholeString = "";
        }
        if (str_buf != "" ){
            pch=strchr(buffer,'_');
            foundNP1 = pch-buffer+1 ;
            pch=strchr(pch+1,'_');
            foundVP = pch-buffer+1 ;
            str = str_buf.substr (foundNP1, (foundVP - foundNP1)-2 ); 
            wholeString = wholeString + " " + str ;}
    }
        lemmed.close();
        lemmed.clear();
        lemm_words.close();
        lemm_words.clear();


    /////////////

    inout.open(FILE_ANNA_BEFORE_SPLIT);
    for(int i=0; i < storyWordInfo.size(); i++){
        if (storyWordInfo[i].StoryTimeEnd == "" && storyWordInfo[i].StoryTimeStart == ""
            && storyWordInfo[i].StoryTopicName == "" ){
            Count++;
            if (storyWordInfo[i].Verb_Ph == ""){ 
                inout << "this" << endl; // add stop word to empty line
            }else{
                inout << storyWordInfo[i].Verb_Ph << endl;
            }
        }
    }
    inout.close();


    system(CMD_split.c_str());
    system(CMD_lemmatize.c_str());

    lemmed.open ("Lemmatizedfile.txt");
    lemmatized_words.clear();                   
    lemm_words.clear() ;
    lemm_words.open ("lemmatized_words.txt");

    while (!lemmed.eof() && lemmed.good() ) {
        lemmed.getline(buffer, 500, '\n');
        str_buf = (buffer);

        if (str_buf == "") {
        lemmatized_words.push_back(wholeString);
        lemm_words << wholeString << '\n';
        Verb_Ph.push_back(wholeString);
        //entry.Verb_Ph = wholeString;
        //FinalTriplet.push_back(entry);
        wholeString = "";
        }
        if (str_buf != "" ){
        pch=strchr(buffer,'_');
        foundNP1 = pch-buffer+1 ;
        pch=strchr(pch+1,'_');
        foundVP = pch-buffer+1 ;
        str = str_buf.substr (foundNP1, (foundVP - foundNP1)-2 ); 
        wholeString = wholeString + " " + str ;}
    }
        lemmed.close();
        lemmed.clear();
        lemm_words.close();
        lemm_words.clear();

    ////////

    inout.open (FILE_ANNA_BEFORE_SPLIT);
    for(int i=0; i < storyWordInfo.size(); i++){
        if (storyWordInfo[i].StoryTimeEnd == "" && storyWordInfo[i].StoryTimeStart == ""
            && storyWordInfo[i].StoryTopicName == "" ){
            Count++;
            if (storyWordInfo[i].Non_Ph2 == ""){ 
                inout << "this" << endl; // add stop word to empty line
            }else{
                inout << storyWordInfo[i].Non_Ph2 << endl;
            }
        }
    }
    inout.close();

    system(CMD_split.c_str());
    system(CMD_lemmatize.c_str());

    lemmed.open ("Lemmatizedfile.txt");
    lemmatized_words.clear();                   
    lemm_words.clear() ;
    lemm_words.open ("lemmatized_words.txt");

    while (!lemmed.eof() && lemmed.good()) {
        lemmed.getline(buffer, 500, '\n');
        str_buf = (buffer);

        if (str_buf == "") {
            lemmatized_words.push_back(wholeString);
            lemm_words << wholeString << '\n';
            Non_Ph2.push_back(wholeString);
            //entry.Verb_Ph = wholeString;
            //FinalTriplet.push_back(entry);
            wholeString = "";
        }
        if (str_buf != "" ){
            pch=strchr(buffer,'_');
            foundNP1 = pch-buffer+1 ;
            pch=strchr(pch+1,'_');
            foundVP = pch-buffer+1 ;
            str = str_buf.substr (foundNP1, (foundVP - foundNP1)-2 ); 
            wholeString = wholeString + " " + str ;
        }

    }
    lemmed.close();
    lemmed.clear();
    lemm_words.close();
    lemm_words.clear();

    int Counter;
    int StoryIndex = 0, StoryCount = 0;
    for(int i=0; i < Non_Ph1.size()-1; i++){

        for (Counter = 0; Counter < StoryNameAndSenNum[StoryIndex].NumOFSenInOneStory; Counter++){
            if (i+Counter < Non_Ph1.size()){
                entry.Non_Ph1 = Non_Ph1[i+Counter];
                entry.Verb_Ph = Verb_Ph[i+Counter];
                entry.Non_Ph2 = Non_Ph2[i+Counter];
                entry.StoryName = StoryNameAndSenNum[StoryIndex].NameOFStoryTopic;
                entry.StoryTripletsCount = Counter;
                entry.StoryNUmber = StoryNameAndSenNum[StoryIndex].NumOFSenInOneStory;
                storyWordInfoFinal.push_back(entry);
                StoryCount++;
                if(StoryIndex == 321){
                    int Z = 0;
                }
            }
        }
        StoryCount = 0;
        i = i+Counter - 1;
        StoryIndex++;
    }
    
    vector<string> removeList(stopwordsArray,
                        stopwordsArray + sizeof(stopwordsArray)/ sizeof(stopwordsArray[0]));
    //cout <<"removeList.size   "<<removeList.size()<<endl;

            for(int i=0; i < removeList.size(); i++){
                for (int j=i+1; j < removeList.size(); j++){
                    if (removeList[i].compare(removeList[j]) == 0){
                        removeList.erase (removeList.begin()+j);
                        j--;}}}


        string wholeStringNon_Ph1 , wholeStringNon_Ph2 ;
        size_t found;
        for(int i=0; i < storyWordInfoFinal.size(); i++){ 
        
        wholeStringNon_Ph1 = storyWordInfoFinal[i].Non_Ph1;
        wholeStringNon_Ph2 = storyWordInfoFinal[i].Non_Ph2;
        wholeString = storyWordInfoFinal[i].Verb_Ph;
        
        char chars[] = "1234567890,:'";

           for (unsigned int ii = 0; ii < sizeof(chars); ++ii)
           {
              // you need include <algorithm> to use general algorithms like remove()
              wholeString.erase (remove(wholeString.begin(), wholeString.end(), chars[ii]), wholeString.end());
              wholeStringNon_Ph1.erase (remove(wholeStringNon_Ph1.begin(), wholeStringNon_Ph1.end(), chars[ii]), wholeStringNon_Ph1.end());
              wholeStringNon_Ph2.erase (remove(wholeStringNon_Ph2.begin(), wholeStringNon_Ph2.end(), chars[ii]), wholeStringNon_Ph2.end());
           }

        replace( wholeString.begin(), wholeString.end(), '-', ' ' );
        replace( wholeStringNon_Ph1.begin(), wholeStringNon_Ph1.end(), '-', ' ' );
        replace( wholeStringNon_Ph2.begin(), wholeStringNon_Ph2.end(), '-', ' ' );

        storyWordInfoFinal[i].Non_Ph1 = wholeStringNon_Ph1;
        storyWordInfoFinal[i].Non_Ph2 = wholeStringNon_Ph2;
        storyWordInfoFinal[i].Verb_Ph = wholeString;

        }


        for (int k = 0; k < 3; k++){

            for(int i=0; i < storyWordInfoFinal.size(); i++){
                vector<string> words;

                istringstream iss;
                if ( k == 0 ){
                istringstream iss(storyWordInfoFinal[i].Non_Ph1);
                copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
                }else if ( k == 1 ){
                istringstream iss(storyWordInfoFinal[i].Non_Ph2);
                copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
                }else if ( k == 2 ){
                istringstream iss(storyWordInfoFinal[i].Verb_Ph);
                copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
                }

            for(int kk=0; kk < words.size(); kk++){
                for (int jj=0; jj < removeList.size(); jj++){

                    if (words[kk].compare(removeList[jj]) == 0){
                        words[kk] = "" ;}
                }
            }

            wholeString.clear();
            for(int kk=0; kk < words.size(); kk++){
                if ( words[kk] != "" ){
                        wholeString = wholeString + " " + words[kk] ;
                }
            }

            if ( k == 0 ){
                found = wholeString.find("'s");
                if (found <= 50){
                    wholeString.erase (found,2);}
            found = wholeString.find("$");
            if (found <= 50){
                wholeString = "dollar";}        
                storyWordInfoFinal[i].Non_Ph1 = wholeString;

            }else if ( k == 1 ){
            found = wholeString.find("'s");
            if (found <= 50){
                wholeString.erase (found,2);}
                found = wholeString.find("$");
            if (found <= 50){
                wholeString = "dollar";}
                storyWordInfoFinal[i].Non_Ph2 = wholeString;
                found = wholeString.find("united state");
            if (found <= 50){
                wholeString = "u.s.";}
                storyWordInfoFinal[i].Non_Ph2 = wholeString;
                found = wholeString.find("'");
            if (found <= 50){
                wholeString.erase (found,1);}
                storyWordInfoFinal[i].Non_Ph2 = wholeString;

            }else if ( k == 2 ){
            found = wholeString.find("'s");
            if (found <= 50){
                wholeString.erase (found,2);}
            found = wholeString.find("$");
                if (found <= 50){
                wholeString = "dollar";}
                storyWordInfoFinal[i].Verb_Ph = wholeString;
            }

        }

        }
    return storyWordInfoFinal;
}
                

// Using WordNet to calculate the similarity
// Using R to do the Hierarchical cluster
void TextAnalysis::CalculateSimilarity(vector<FinalTriplet> & storyWordInfoFinal)
{
    vector<StoryInfo> StoryInfoForSim;
    StoryInfoForSim.clear();
    vector<string> Np1;
    vector<string> Vp;
    vector<string> Np2;

    StoryInfo entry;
    for(int i=0; i < storyWordInfoFinal.size(); i++)
    {
        if (storyWordInfoFinal[i].StoryTripletsCount  == 0)
        {
            entry.StoryTopic = storyWordInfoFinal[i].StoryName;
        }

        if ( storyWordInfoFinal[i].StoryTripletsCount != storyWordInfoFinal[i].StoryNUmber-1)
        {
            if ( storyWordInfoFinal[i].Non_Ph1 != "")
            {
                Np1.push_back(storyWordInfoFinal[i].Non_Ph1);
            }
            if ( storyWordInfoFinal[i].Verb_Ph != "")
            {
                Vp.push_back(storyWordInfoFinal[i].Verb_Ph);
            }
            if ( storyWordInfoFinal[i].Non_Ph2 != "")
            {
                Np2.push_back(storyWordInfoFinal[i].Non_Ph2);
            }  
        }
        
        if ( storyWordInfoFinal[i].StoryTripletsCount == storyWordInfoFinal[i].StoryNUmber-1)
        {
            entry.NP1 = Np1;
            entry.VP = Vp;
            entry.NP2 = Np2;
            StoryInfoForSim.push_back(entry);
            Np1.clear();
            Vp.clear();
            Np2.clear();
        }
    }

    //
    // Compute similarities using WordNet.
    //
    size_t found;
    ofstream inout;
    inout.open ("output/ForSim.txt");
    for(int i=0; i< StoryInfoForSim.size();i++)
    {
        if (StoryInfoForSim[i].NP1.size()>0)
        {
            for(int j=0; j< StoryInfoForSim[i].NP1.size();j++)
            {
                inout << StoryInfoForSim[i].NP1[j] << endl;
            }
        }
    }
    inout.close();

    char sysCmdForJave[1024];
    char buf4[10];
    strcpy(buf4, "n");
    sprintf(sysCmdForJave, "java -Xmx1g -jar WNsim.jar %s %s", buf4 , "output/ForSim.txt");
    system(sysCmdForJave);

    //
    // Readin WordNet scores from text file.
    //
    string str;
    vector<double> AllScore;
    ifstream ifs;

    ifs.open("out.txt", ios::in);
    if (!ifs.is_open()) cout<<"out.txt File NOT opened"<<endl;
    while (!ifs.eof() && ifs.good() ) {
        char buffer[128];
        ifs.getline(buffer, 128);
        str = (buffer);
        double num = atof( str.c_str() );
        AllScore.push_back(num);
    }
    cout<<"AllScore Size  "<<AllScore.size()<<endl;  //// AllScore SIZE neeeed to be minus one 

    // 
    // Create a similarity matrix.
    //
    int MatLength = sqrt ( AllScore.size()-1);
    vector<vector <double> > Score_Mat;
    vector<double> Building_Mat;
    for(int i=0; i < MatLength; i++){ 
        Building_Mat.push_back(0);}
    for(int i=0; i < MatLength; i++){   
        Score_Mat.push_back(Building_Mat);}


    vector<vector <double> > Sim_Mat;
    Building_Mat.clear();
    for(int i=0; i < StoryInfoForSim.size(); i++){ 
        Building_Mat.push_back(0);}
    for(int i=0; i < StoryInfoForSim.size(); i++){  
        Sim_Mat.push_back(Building_Mat);}

    int Count=0;
    for(int j=0; j < Score_Mat.size(); j++){ 
        for(int k=0; k < Score_Mat.size() ; k++){ 
            Count++;
            Score_Mat[j][k] = AllScore[Count-1];
        }
    }

    vector<double>MaxVector;
    Count=0;int Count1=0;
    for(int i=0; i < StoryInfoForSim.size(); i++)
    {
        for(int ii=0; ii < StoryInfoForSim.size(); ii++)
        {

            double Ave=0;
            for(int j=0+Count; j < StoryInfoForSim[i].NP1.size()+Count; j++)
            {
                double Max= Score_Mat[j][Count1];
                for(int k=0+Count1; k < StoryInfoForSim[ii].NP1.size()+Count1; k++)
                {
//                  Ave = Ave+ Score_Mat[j][k];
                    if (Max < Score_Mat[j][k])
                    {
                        Max = Score_Mat[j][k];
                    }
                }
                MaxVector.push_back(Max);
            }
        
            for (int z=0; z<MaxVector.size();z++)
            {
                Ave = Ave+MaxVector[z];
            }
            Ave = Ave/MaxVector.size();MaxVector.clear();
            Sim_Mat[i][ii]=Ave;
            Count1=Count1+StoryInfoForSim[ii].NP1.size();

        }
        Count=Count+StoryInfoForSim[i].NP1.size();
        Count1=0;
    }

    for(int i=0; i<Sim_Mat.size(); i++)
    {
        for(int j=0; j<Sim_Mat.size(); j++)
        {
            Sim_Mat[j][i] = Sim_Mat[i][j];
        }
    }

    for(int i=0; i<Sim_Mat.size(); i++)
    {
        for(int j=0; j<Sim_Mat.size(); j++)
        {
            Sim_Mat[i][j] = 1- Sim_Mat[i][j];
        }
    }
    for(int i=0; i<Sim_Mat.size(); i++)
    {
        Sim_Mat[i][i] = 0;
    }

    //
    // Save similarity matrix in a file.
    //
    Count=0;
    char Simi = '"';
    inout.open ("Sim_Mat");
    string WholeNumber;
    for(int i=0; i<Sim_Mat.size(); i++)
    {
        for(int j=0; j<Sim_Mat.size(); j++)
        {
            inout<<Sim_Mat[i][j];
            if(j<Sim_Mat.size()-1)
            {
                inout<<" ";
            }
            Count++;
        }
        inout<<'\n';
    }
    inout.close();

    inout.open ("Story_Name");
    for(int i=0; i<StoryInfoForSim.size(); i++){

        inout << Simi << StoryInfoForSim[i].StoryTopic << Simi;
        if(i < StoryInfoForSim.size()-1)
        {
            inout<<" ";
        }
    }
    inout.close();

    //
    // Using R to do the hierarchical clustering.
    //
    system("R CMD BATCH hcscript.r");
}


void TextAnalysis::Screen_Text_Info(
    OUT vector<ScreenInfo> &Screen_Info_Final, 
    OUT set<string> &screen_vocabulary,
    string orcDir,  
    string annotatedTextDir,
    string newsListFilename)
{
    
    ofstream TestForDebug; 
    TestForDebug.clear();
    string str, str1, str2, str3, str_frame="0000", Screen_line="000", Screen_Frame="0000",StartPoint, words;   

    size_t found , found1, found2, found3;
    vector<StoryElements> Story_Info;
    vector<ScreenText> Screen_Info;
    vector<string> Story_Word;
    vector<ScreenText> Annotated_Screen_Info;
    StoryElements entry;
    ScreenText onScreenText;
    int Iindix=0 , Iindix1=0, Iindix2=0;
    
    ifstream ifsNewsList;
    ifsNewsList.open(newsListFilename.c_str(), ios::in);
    if (!ifsNewsList.is_open())
        cout<<"File NOT opened"<<endl;
    
    double Base; 
    while (!ifsNewsList.eof() && ifsNewsList.good())
    {

        string bufferstr = "";
        getLineNew(ifsNewsList, bufferstr);
        string newsPrefix = bufferstr;

        string Year,Month,Day;
        if(newsPrefix != "")
        {
            Year = newsPrefix.substr(0 , 4);
            Month = newsPrefix.substr(5 , 2);
            Day = newsPrefix.substr(8 , 2);         
        }


        // /sweep/2008/2008-08/2008-08-08/
        string orcFilename = (orcDir + newsPrefix + ".ocr.jpg.ocr");        
        string captionFileName = ("/sweep/"+Year+"/"+Year+"-"+Month+"/"+Year+"-"+Month+"-"+Day+"/" + newsPrefix +".txt");

        ifstream ifsOCR;
        ifsOCR.open(orcFilename.c_str(), ios::in);
        if (!ifsOCR.is_open()) cout<<"orcFilename File NOT opened"<<endl;

        ifstream ifsCaption;
        ifsCaption.open(captionFileName.c_str(), ios::in);
        if (!ifsCaption.is_open()) cout<<"captionFileName File NOT opened"<<endl;

        Iindix2=0;

        //
        // extract Story info(Start, End, Category, Topic) from old annotaded
        //
        while (!ifsCaption.eof() && ifsCaption.good() )
        {
            string bufferstr = "";
            getLineNew(ifsCaption, bufferstr);
            str = (bufferstr);          
            
            found = str.find("SegStart");
            found1 = str.find("SegStart-NEW");


            if (found==0 && Iindix2==0)
            {
                StartPoint = str.substr(9 , 14);
                StartPoint[10] = '0';
                StartPoint[11] = '0';
                StartPoint[12] = '0';
                StartPoint[13] = '0';
                Base = atof( StartPoint.c_str() );  // %Y%m%d%H
                Iindix2=1;
            }
            if ( found == 0 && Iindix ==0 && found1 != 0)
            {
                string Cat_Topic = str.substr(28 , str.size());
                found1 = Cat_Topic.find("|");
                string Cat = Cat_Topic.substr(0 , found1);
                string Top = Cat_Topic.substr(found1+1 , Cat_Topic.size() );
                string Start = str.substr(9 , 18);
                double StartPoint = atof(Start.c_str());
                entry.StoryTimeStart = StartPoint;

                entry.StoryCat = Cat;
                entry.StoryTopic = Top;
                Iindix = 1;
            }

            found1 = str.find("SegEnd");
            found = str.find("SegEnd-NEW");
            if (found1 == 0 && Iindix1 ==0 && found != 0)
            {
                string End = str.substr(7 , 18);
                double EndPoint = atof(End.c_str() );
                entry.StoryTimeEnd = EndPoint;
                Iindix1 = 1;
            }
            found2 = str.find("CCO");
            if ( found2 == 0)
            {
                string Word_inEachline= str.substr( 23 , str.size());
                words = words + Word_inEachline + " ";
            }
            if (found1 == 0 && found != 0 )
            {   
                entry.Words = words;
                Story_Info.push_back(entry);
                Iindix = 0;
                Iindix1 = 0;
                words.clear();
            }
        }

        Iindix = 0;

        //
        // Extract onscreen information from OCR file.
        //
        while (!ifsOCR.eof() && ifsOCR.good())
        {
            string bufferstr = "";
            getLineNew(ifsOCR, bufferstr);
            str = (bufferstr);

            found = str.find("|");
            found1 = str.find("OCR1|");
            if (str != ""){
                // st1 is the time stamp and line number part
                str1 = str.substr (0, found );

                // time stamp %m%s
                Screen_Frame[0] = str1[10];
                Screen_Frame[1] = str1[11];
                Screen_Frame[2] = str1[12];
                Screen_Frame[3] = str1[13];

                Screen_line[0] = str1[15];
                Screen_line[1] = str1[16];
                Screen_line[2] = str1[17];

                // str2 is the substring after "OCR1|"
                str2 = str.substr (found1+5 , str.size() );
                found = str2.find("|");

                // str2 is now the content of on sctreen text
                str2 = str2.substr (0, found );         //cout << str1 + str2 << endl;      
                double Screen_Frame1 = atoi ( Screen_Frame.c_str() );
                double Screen_line1 = atoi ( Screen_line.c_str() ); 

                onScreenText.Screen_Frame1 = Screen_Frame1 ;
                onScreenText.Screen_line1 = Screen_line1;
                onScreenText.Base = Base;       // FIXME: Base is not changing within this loop
                onScreenText.Screen_Topic = (str2);
                Screen_Info.push_back(onScreenText);
            }
        }
        ifsOCR.close();
        ifsCaption.close();
    }

    int currentFrameID = 0;
    vector<int> Removable_Line;
    vector<string> Removable_list;
    vector<string> Removable_list_First_Line;
    vector<string> Removable_list_Last_Line;
    int Max_Line=0;

    //find "Moving Bar" for remove
    for (int i=0; i< Screen_Info.size(); i++)
    {
        if ( Screen_Info[i].Screen_Frame1 == currentFrameID )
        {
             Max_Line =  Screen_Info[i].Screen_line1;
        }
        if ( i< Screen_Info.size()-1)
        {
            if (Screen_Info[i+1].Screen_Frame1 != currentFrameID && Max_Line>2)
            {
                if (Max_Line > 2)
                {
                    Removable_Line.push_back(i-Max_Line);
                    Removable_list_First_Line.push_back( Screen_Info[i-Max_Line].Screen_Topic);
                    Removable_Line.push_back(i-Max_Line+1);
                    Removable_list_First_Line.push_back( Screen_Info[i-Max_Line].Screen_Topic);
                }
                Removable_Line.push_back(i);
                Removable_list_Last_Line.push_back( Screen_Info[i].Screen_Topic);
            }
            if ( Screen_Info[i+1].Screen_Frame1 != currentFrameID )
            {
                currentFrameID = Screen_Info[i+1].Screen_Frame1;
            }
        }
    }

    // Remove the "Moving Bar" from the list
    vector<ScreenText> onScreenInfoTemp;
    int indix=0;
    for (int i=0; i< Screen_Info.size(); i++)
    {       
        if (indix < Removable_Line.size())
        {
            if (i == Removable_Line[indix])
            {
                indix++;
            }
            else
            {
                onScreenInfoTemp.push_back(Screen_Info[i]);
            }
        }
        else // Added by Hang  3/1/2013
        {
            onScreenInfoTemp.push_back(Screen_Info[i]);
        }
    }
    Screen_Info.clear();
    Screen_Info = onScreenInfoTemp;

    // Base +
    // Recover full time stamp
    for (int i=0; i< Screen_Info.size(); i++)
    {
        Screen_Info[i].Screen_Frame1 = Screen_Info[i].Base + Screen_Info[i].Screen_Frame1 + (Screen_Info[i].Screen_line1/1000);
    }

    for (int i=0; i< Story_Info.size(); i++)
    {

        ScreenInfo entry2;
        string Whole_String;        
        for (int j=0; j< Screen_Info.size(); j++)
        {
            if( Story_Info[i].StoryTimeStart<Screen_Info[j].Screen_Frame1 && 
                Screen_Info[j].Screen_Frame1<Story_Info[i].StoryTimeEnd )
            {
                Whole_String = Whole_String + " " +Screen_Info[j].Screen_Topic;
            }
        }
        entry2.StoryTimeStart = Story_Info[i].StoryTimeStart;
        entry2.StoryTimeEnd = Story_Info[i].StoryTimeEnd;
        string StoryTitle = Story_Info[i].StoryCat + "|" + Story_Info[i].StoryTopic;
        string StoryCateg = Story_Info[i].StoryCat;
        entry2.CatName = StoryCateg;
        entry2.StoryTopicName = StoryTitle; 
        entry2.Screen_words = Whole_String;
        Screen_Info_Final.push_back(entry2);

    }

    //
    // Get rid of commercials content,
    // combine words with same lemma, and remove stop words.
    //

    // Remove words in commercials and introductions
    size_t foundNP1, foundVP ;

    vector<string> Screen_Words ;
    for (int ii = 0; ii < 2; ii++)
    {
        ofstream inout ;ofstream inout1 ;
        inout.clear() , inout1.clear();

        // First iteration: output all on screen words (from ocr files)
        if (ii == 0)
        {
            Screen_Words.clear();       
            inout.open (FILE_ANNA_BEFORE_SPLIT, ios::out | ios::binary );
            for(int i=0; i < Screen_Info_Final.size(); i++)
            {

                if (Screen_Info_Final[i].Screen_words == "" || 
                    Screen_Info_Final[i].CatName == "Commercial" ||
                    Screen_Info_Final[i].StoryTopicName == "Network|Intro")
                {
                    inout << "this" << endl; // add stop word to empty line
                }
                else
                {
                    inout << Screen_Info_Final[i].Screen_words << endl;
                }
            }
        }
        else if (ii == 1)
        {
            // Second iteration: output all story words (from caption files)

            Screen_Words.clear() ;
            inout.open (FILE_ANNA_BEFORE_SPLIT, ios::out );
            for(int i=0; i < Story_Info.size(); i++)
            {
                string StoryTitle = Story_Info[i].StoryCat + "|" + Story_Info[i].StoryTopic;
                if (Story_Info[i].Words == "" || 
                    Story_Info[i].StoryCat == "Commercial" ||
                    StoryTitle == "Network|Intro")
                { 
                    inout << "this" << '\n'; // add stop word to empty line
                }
                else
                {
                    inout << Story_Info[i].Words <<" "<< '\n';
                }
            }

        }
        inout.close();

        // Prepare text
        // reference: https://code.google.com/p/mate-tools/wiki/Preparing_Text_Lemmatizing_Tagging_Morphologic_Tagging

        // Splits a tokenized sentences into one word per line format:
        string CMD_split = "java -cp " FILE_ANNA_JAR " is2.util.Split " FILE_ANNA_BEFORE_SPLIT " > " FILE_ANNA_AFTER_SPLIT;
        system(CMD_split.c_str());
        
        // Lemmatize: combine words with prefix / suffix variations
        string CMD_lemmatize = "java -Xmx2G -cp " FILE_ANNA_JAR " is2.lemmatizer.Lemmatizer -model " FILE_LEMMA_ENG_MODEL " -test " FILE_ANNA_AFTER_SPLIT " -out Lemmatizedfile.txt";
        system(CMD_lemmatize.c_str());

        ifstream lemmed ("Lemmatizedfile.txt");
        char buffer[500];
        char * pch;
        vector<string> lemmatized_words;
        string wholeString , str_buf , str12  ;                     
        ofstream lemm_words ;
        lemm_words.open ("lemmatized_words.txt");

        while (!lemmed.eof() && lemmed.good()) 
        {
            lemmed.getline(buffer, 500, '\n');
            str_buf = (buffer);

            if (str_buf != "" )
            {
                pch=strchr(buffer,'_');
                foundNP1 = pch-buffer+1 ;
                pch=strchr(pch+1,'_');
                foundVP = pch-buffer+1 ;
                str = str_buf.substr (foundNP1, (foundVP - foundNP1)-2 ); 
                found = str.find("$");
                if (found <= 55){
                str = "dollar";}
                found = str.find("u.s.");
                if (found <= 55){
                str = "United_States";}         
                wholeString = wholeString + " " + str ;
            }
            if (str_buf == "") 
            {
                lemmatized_words.push_back(wholeString);
                lemm_words << wholeString << '\n';

                Screen_Words.push_back(wholeString);
                wholeString = "";
            }
        }
        lemmed.close();
        lemmed.clear();
        lemm_words.close();
        lemm_words.clear();


        // initiate a vector of stop words from the predefined array
        vector<string> removeList(stopwordsArray,
                        stopwordsArray + sizeof(stopwordsArray)/ sizeof(stopwordsArray[0]));

        // remove duplicates
        for(int i=0; i < removeList.size(); i++)
        {
            for (int j=i+1; j < removeList.size(); j++)
            {
                if (removeList[i].compare(removeList[j]) == 0)
                {
                    removeList.erase (removeList.begin()+j);
                    j--;
                }
            }
        }

        // filter out numbers and punctuations.
        for(int i=0; i < Screen_Words.size(); i++)
        {       
            wholeString = Screen_Words[i];
            char chars[] = "1234567890.,:'?";
            for (unsigned int j = 0; j < sizeof(chars); ++j)
            {               
                wholeString.erase (remove(wholeString.begin(), wholeString.end(), chars[j]), wholeString.end());
            }
            replace( wholeString.begin(), wholeString.end(), '-', ' ' );
            Screen_Words[i] = wholeString;
        }

        // remove stop words
        if (ii == 0)
        {
            // Iteration 1: on screen text
            for(int i=0; i < Screen_Words.size()-1; i++)
            {
                vector<string> words;
                istringstream iss(Screen_Words[i]);
                copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
                for(int kk=0; kk < words.size(); kk++)
                {
                    for (int jj=0; jj < removeList.size(); jj++)
                    {
                        if (words[kk].compare(removeList[jj]) == 0)
                        {
                            // in stop word list, don't keep
                            words[kk] = "" ;
                        }
                    }
                }

                wholeString.clear();
                for(int kk=0; kk < words.size(); kk++)
                {
                    if ( words[kk] != "" )
                    {
                        wholeString = wholeString + " " + words[kk] ;
                    }
                }   
                Screen_Info_Final[i].Screen_words = wholeString;
            }
        }
    
        if (ii == 1)
        {
            // Iteration 2: story words (from captions)
            for(int i=0; i < Screen_Words.size()-1; i++)
            {
                vector<string> words;
                istringstream iss(Screen_Words[i]);
                copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
                for(int kk=0; kk < words.size(); kk++)
                {
                    for (int jj=0; jj < removeList.size(); jj++)
                    {
                        if (words[kk].compare(removeList[jj]) == 0)
                        {
                            words[kk] = "" ;
                        }
                    }
                }
                wholeString.clear();
                for(int kk=0; kk < words.size(); kk++)
                {
                    if ( words[kk] != "" )
                    {
                        wholeString = wholeString + " " + words[kk] ;
                    }
                }

                Story_Info[i].Words = wholeString;
            }
        }
    }


    for (int z=0; z < Screen_Info_Final.size(); z++)
    {
        vector<string> Sc_words;
        vector<string> Cc_words;

        istringstream iss(Screen_Info_Final[z].Screen_words);
        copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(Sc_words));

        istringstream iss1(Story_Info[z].Words);
        copy (istream_iterator<string>(iss1), istream_iterator<string>(), back_inserter(Cc_words));

        // FIXME: What does the remain words mean?
        string Remain_ScWords;
        vector<string> Remain_ScWords1;
        for (int j=0; j<Sc_words.size(); j++)
        {   
            for (int k=0; k<Cc_words.size(); k++)
            {
                if (Sc_words[j].compare(Cc_words[k]) == 0)
                {
                    Remain_ScWords = Sc_words[j] + " " + Remain_ScWords ;
                    Remain_ScWords1.push_back(Sc_words[j]);
                }
            }
        }
        Screen_Info_Final[z].Screen_words = Remain_ScWords;

        // remove duplicates
        for(int i=0; i < Remain_ScWords1.size(); i++)
        {
            for (int j=i+1; j < Remain_ScWords1.size(); j++)
            {
                if (Remain_ScWords1[i] != "" )
                {
                    if (Remain_ScWords1[i].compare(Remain_ScWords1[j]) == 0)
                    {
                        Remain_ScWords1.erase (Remain_ScWords1.begin()+j);
                        j--;
                    }
                }
            }
        }
        for(int i=0; i < Remain_ScWords1.size(); i++)
        {
            screen_vocabulary.insert(Remain_ScWords1[i]);
        }
    }
}

/*void TextAnalysis::SaveVocabulary(set<string> vocabulary, string dest_filename)
{
    ofstream inout;
    inout.open(dest_filename.c_str());
    std::for_each(vocabulary.begin(), vocabulary.end(), [&] (string word) {
          inout << word << endl;
    });
    inout.close();
}*/

vector<ScreenInfo> TextAnalysis::RemoveShortStory_ScreenTopic(
    const vector<ScreenInfo> &screenInfo_org, 
    vector<int> & RemovedStory)
{                                               
    vector<int> Remove_Commercial_Teaser;
    vector<ScreenInfo> screenInfo = screenInfo_org;
    
    // Remove stories in the given list.
    int iIndix=0;
    for (int i=0; i < RemovedStory.size(); i++)
    {
        int j = RemovedStory[i] - iIndix ;
        screenInfo.erase(screenInfo.begin() + j);
        iIndix++ ;
    }

    // 
    // remove teasers or commercials
    // 
    for (int i=0; i < screenInfo.size(); i++)
    {
        auto found = screenInfo[i].StoryTopicName.find("Teaser");
        auto found1 = screenInfo[i].StoryTopicName.find("Commercial");
        auto found2 = screenInfo[i].StoryTopicName.find("NULL");
        if ( found < 50 || found1 < 50 || found2 < 50 ){
            Remove_Commercial_Teaser.push_back(i);
        }
    }

    iIndix=0;
    for (int i=0; i < Remove_Commercial_Teaser.size(); i++)
    {
        int j = Remove_Commercial_Teaser[i] - iIndix ;
        screenInfo.erase(screenInfo.begin() + j);
        iIndix++ ;}

    for (int i=0; i<screenInfo.size(); i++){

    }

    //
    // remove introductions
    //
    Remove_Commercial_Teaser.clear();
    for (int i=0; i < screenInfo.size(); i++)
    {
        auto found = screenInfo[i].StoryTopicName.find("Network|Intro");
        if ( found < 50 ){
            Remove_Commercial_Teaser.push_back(i);
        }
    }

    iIndix=0;
    for (int i=0; i < Remove_Commercial_Teaser.size(); i++)
    {
        int j = Remove_Commercial_Teaser[i] - iIndix ;
        screenInfo.erase(screenInfo.begin() + j);
        iIndix++ ;
    }

    //
    // remove stories has no words
    //
    Remove_Commercial_Teaser.clear();
    for (int i=0; i < screenInfo.size(); i++)
    {
        if ( screenInfo[i].Screen_words == "")
        {
            Remove_Commercial_Teaser.push_back(i);
        }
    }

    iIndix=0;
    for (int i=0; i < Remove_Commercial_Teaser.size(); i++)
    {
        int j = Remove_Commercial_Teaser[i] - iIndix ;
        screenInfo.erase(screenInfo.begin() + j);
        iIndix++ ;
    }

    //
    // Remove stories has less than 200 words.
    //
    Remove_Commercial_Teaser.clear();
    for (int i=0; i<screenInfo.size(); i++)
    {
        int SenSize = screenInfo[i].Screen_words.size();
        if ( SenSize < 200 )
        {
            Remove_Commercial_Teaser.push_back(i);
        }
    }

    iIndix=0;
    for (int i=0; i<Remove_Commercial_Teaser.size(); i++)
    {
        int j = Remove_Commercial_Teaser[i] - iIndix ;
        screenInfo.erase(screenInfo.begin() + j);
        iIndix++ ;
    }

    return std::move(screenInfo);
}


 void TextAnalysis::ParameterLearning_ScreenTopic(
        vector<ScreenInfo> &Screen_Info_Final,
        const set<string> & vocabulary){

    string str, str1, str2 ;
    size_t found, found1, found3, founf4;   
    ofstream fout_eval, fout_enhance;
    fout_eval.open("output/OnScreenText_CrossValidation.txt");
    fout_enhance.open("output/OnScreenText_ConfusionMatrix.txt");

    vector<ScreenInfo> Screen_Info_FinalOrg;

    vector<vector <int> > confusion_matrix;
    vector<int> building_mat;
    building_mat.resize(NUM_CATEGORIES, 0);
    for(int i=0; i < NUM_CATEGORIES; i++)
    {   
        confusion_matrix.push_back(building_mat);
    }

    // Partition whole datasets into several testing sets for cross validation.
    int TrainSet = 0, TestSet = 0, CountForTrainSet = 0, TotalSt = 0;
    int num_stories = Screen_Info_Final.size();

    vector<int> TestPeriod;
    TestPeriod.push_back(0);
    TestSet = num_stories/10 +1 ;
    TrainSet = num_stories - TestSet;
    Screen_Info_FinalOrg = Screen_Info_Final;   

    // partition
    for( int i=0; i < Screen_Info_Final.size(); i++)
    {
        for ( int Iindex = i; Iindex < TestSet + i; Iindex++ )
        {
            if(Iindex < Screen_Info_Final.size())
            {
                TotalSt++;      
            }
        }
        TestPeriod.push_back(TotalSt);
        i=i+TestSet-1;
    }
    fout_eval << "Number of Stories in All Documents: " << num_stories << endl;

    // Cross validation
    const char* array[] = {"War", "Sports", "Disaster", "Accident",
            "Activism", "Weather", "Social","Government","Science-technology",
            "Religion","Politics", "International", "Lifestyle-leisure",
            "Labor", "Human-interest", "Health", "Environment", "Education",
            "Business", "Money", "Crime", "Justice", "Art-culture",
            "Celebrity", "Entertainment", "Network" , "Commercial"};
    vector<string> categories(array, array + sizeof array / sizeof array[0]);


    vector<double> crossValidation;
    for (int kkk=0; kkk<TestPeriod.size()-1; kkk++)
    {
        vector<ScreenInfo> screenInfo_testing;
        vector<ScreenInfo> screenInfo_training;
        
        // partition into training set and testing set
        for (int i=0; i<Screen_Info_FinalOrg.size(); i++)
        {
            if(TestPeriod[kkk] <= i &&  i < TestPeriod[kkk+1] )
            {
                screenInfo_testing.push_back(Screen_Info_FinalOrg[i]);
            }
            else
            {
                screenInfo_training.push_back(Screen_Info_FinalOrg[i]);
            }
        }

        // extract annotated labels
        vector<string> labels_training;
        for(int i=0; i < screenInfo_training.size(); i++)
        {
            string str = screenInfo_training[i].StoryTopicName;
            found1 = str.find('|');
            str1 = str.substr ( 0, found1 );
            found = str1.find(':');
            if (found < 50 )
            {
                str1 = str1.substr (0, found);
            }
            if (str1 != "NULL" )
            {
                labels_training.push_back(str1);
            }
        }

        vector<string> labels_testing;
        for( int i=0; i < screenInfo_testing.size(); i++)
        {
            string str = screenInfo_testing[i].StoryTopicName;
            found1 = str.find('|' );
            str1 = str.substr ( 0, found1 );
            found = str1.find(':' );
            if (found < 50 )
            {
                str1 = str1.substr ( 0, found );
            }
            if (str1 != "NULL" )
            {
                labels_testing.push_back(str1);
            }
        }
        
        //
        //
        //      
        
        vector<double> prob_cat;

        vector<int> count_cat;
        for(int i=0; i < categories.size(); i++)
        {
            int count = 0;
            for (int j = 0; j < labels_training.size(); j++)
            {
                if (categories[i].compare(labels_training[j]) == 0)
                {
                    count++;
                }
            }
            count_cat.push_back(count);
        }

        // find stories whose label is not in predefined categories.
        vector<int> Additional_Cat_Train;
        vector<int> Additional_Cat_Test;
        for (int j=0; j < labels_training.size(); j++)
        {   
            int count = 0;
            for(int i=0; i < categories.size(); i++)
            {
                if (categories[i].compare(labels_training[j]) == 0)
                {
                    count++;
                    break;  // no need to compare other categories
                }
            }

            if(count==0)
            {
                // the annotated label is not in predefined categories
                Additional_Cat_Train.push_back(j);
            }
        }

        for (int j=0; j < labels_testing.size(); j++)
        {
            int count = 0;
            for(int i=0; i < categories.size(); i++)
            {
                if (categories[i].compare(labels_testing[j]) == 0)
                {
                    count++;
                    break;
                }
            }
            if(count==0)
            {
                Additional_Cat_Test.push_back(j);
            }
        }

        // eliminate stories whose label is not in predefined categories.
        int iIndix=0;
        for (int i=0; i<Additional_Cat_Train.size(); i++){
            int j = Additional_Cat_Train[i] - iIndix ;
            screenInfo_training.erase(screenInfo_training.begin() + j);
            iIndix++ ;
        }
        iIndix=0;
        for (int i=0; i<Additional_Cat_Test.size(); i++){
            int j = Additional_Cat_Test[i] - iIndix ;
            screenInfo_testing.erase(screenInfo_testing.begin() + j);
            iIndix++ ;
        }

        int NumberOfStory = 0;
        NumberOfStory = screenInfo_training.size();
        if (NumberOfStory != labels_training.size()){
            cout<< " Error: Additional Category in Story list which NOT in The Main Category List"<< endl;
        }

        // calculate prior probability for each category.
        for(int i = 0; i < count_cat.size(); i++){
            double prob = double(count_cat[i]) / double(NumberOfStory);
            prob_cat.push_back(prob);
        }

        /*
        // Commented out by Hang 3/27/2013
        // use the set passed in from parameter
        // Loading Dictionary From File 
        ifstream ifs;
        vector<string> vocabularyNP1; 
        ifs.open(vocalubary_filename.c_str() );
        while (!ifs.eof() && ifs.good() ) {
            char buffer[512];
            ifs.getline(buffer, 512);
            str = (buffer);
            if (str != ""){
                vocabularyNP1.push_back(str);}
        }
        ifs.close(); */


        //Creating co-occurrence of (words given cat) AND (words Given Stories) AND P(Wi | Catj)
        vector<vector <double> > WordsCatMatrix;
        vector<vector <double> > prob_wordsGivenCats;
        vector<vector <double> > WordsStoriesMatrix;
        
        vector <double> vec_Categories;
        vec_Categories.resize(categories.size(), 0);
        for(int i=0; i < vocabulary.size(); i++)
        {   
            WordsCatMatrix.push_back(vec_Categories);
            prob_wordsGivenCats.push_back(vec_Categories);
        }
        vec_Categories.clear();
        
        vector<double> vec_wordStories;
        vec_wordStories.resize(NumberOfStory, 0);
        for(int i=0; i < vocabulary.size(); i++)
        {
            WordsStoriesMatrix.push_back(vec_wordStories);
        }
        vec_wordStories.clear();


        // for testing of correctness
        vector<WordCatInfo> WordCatInf;
        vector<WordCatInfo> WordCatInf1;
        vector<WordCatInfo> WordCatInf2;
        WordCatInfo WCInfo;

        // Building  P(Si | Catj) AND P(Catj | Si)
        vector <double> catInfor;
        vector<vector <double> > ProbStoryGivenCat;
        vector<vector <double> > ProbCatGivenStory;
        catInfor.resize(categories.size(), 0);
        for(int i=0; i < NumberOfStory; i++)
        {
            ProbStoryGivenCat.push_back(catInfor);
            ProbCatGivenStory.push_back(catInfor);
        }

        /*
        string *scr;
        scr = new string[vocabulary.size()];

        // convert to lowercase
        for(int j=0; j<vocabulary.size(); j++){
            string data = vocabulary[j];
            transform(data.begin(), data.end(), data.begin(), ::tolower);
            scr[j] = data;
        }
        */

        vector<string> v(vocabulary.begin(), vocabulary.end());
        sort(v.begin(), v.end());

        vector<double> StoriesTime;
        vector<int> story_lens;
        
        sort (v.begin(), v.end());


        // Screen Text
        //
        // Training: calculating probabilities
        //
        for(int idx_story=0; idx_story < screenInfo_training.size(); idx_story++)
        {

            string str = screenInfo_training[idx_story].StoryTopicName;
            found1 = str.find('|' );
            string category = str.substr ( 0, found1 );

            vector<string> words;
            istringstream iss(screenInfo_training[idx_story].Screen_words);
            copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));         
            story_lens.push_back(words.size());

            for(int idx_category = 0; idx_category < categories.size(); idx_category++)
            {
                // find the category
                if (category.compare(categories[idx_category]) == 0)
                {
                    for(int idx_word =0; idx_word < words.size(); idx_word++)
                    {
                        auto low = lower_bound(v.begin(), v.end(), words[idx_word]);
                        string word = *low;
                        int wordId = int(low - v.begin());
                        //cout << "position " << wordId << " "<<word<<"  "<< idx_category <<endl;
                        if (wordId < vocabulary.size() )
                        {
                            WordsCatMatrix[wordId][idx_category] += 1; 
                            WordsStoriesMatrix[wordId][idx_story] += 1;
                        }
                    }
                    break;
                }
            }
        }

        // FIXME: this length probability is not based on range and lens may duplicate.
        vector<double> prob_storylen;
        for (int i=0; i< story_lens.size(); i++)
        {
            double count = 0;
            for (int j=0; j< story_lens.size(); j++)
            {
                if (story_lens[i] == story_lens[j])
                {
                    count = count + 1;
                }
            }
            prob_storylen.push_back(count/double(story_lens.size()));
        }

        // Calculating P(Wi|Catj)
        for (int idx_cat = 0; idx_cat < categories.size(); idx_cat++)
        {
            // calculate normalizing factor.
            double count=0 ;
            for (int idx_word=0; idx_word<vocabulary.size(); idx_word++)
            {
                count = count + WordsCatMatrix[idx_word][idx_cat];
            }

            // convert to probabilities.
            for (int idx_word=0; idx_word<vocabulary.size(); idx_word++)
            {
                if (WordsCatMatrix[idx_word][idx_cat] != 0 && count != 0 )
                {
                    prob_wordsGivenCats[idx_word][idx_cat] = WordsCatMatrix[idx_word][idx_cat]/count;
                }
            }
        }

        //
        // Inference : Find the posterior probability for testing set.
        //
        int correct_count = 0;
        for (int ii = 0; ii < labels_testing.size(); ii++)
        {
            // Read the label for comparison.
            int org_category_idx = 0;
            string labeled_category = labels_testing[ii];
            for ( int i=0; i=categories.size(); i++)
            {
                if (labeled_category.compare(categories[i]) == 0 )
                {
                    org_category_idx = i;
                }
            }
            
            // Calculate posterior probability.
            vector<double> prob_catsGivenStory;

            for(int idx_category=0; idx_category < categories.size(); idx_category++)
            {
                double prob_storyGivenCat=1;

                //for( int idxStory = 0; idxStory < screenInfo_testing.size(); idxStory++)
                //{ 
                vector<string> words;
                istringstream iss(screenInfo_testing[ii].Screen_words);
                copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
                    
                if (words.size() != 0)
                {
                    for(int idx_word=0; idx_word < words.size(); idx_word++)
                    {
                        auto low = lower_bound (v.begin(), v.end(), words[idx_word]);
                        string word = *low;
                        int wordId = int(low- v.begin());

                        // naive Bayes, p(w_i|c) are conditional independent.
                        prob_storyGivenCat = prob_storyGivenCat *
                                prob_wordsGivenCats[wordId][idx_category];
                    }
                }
                //}
                double numerator = prob_cat[idx_category] * prob_storyGivenCat;
                prob_catsGivenStory.push_back(numerator);
            }

            // Predict by the maximum posterior probability (Bayes Decision).
            // Normalize is not necessary.
            int predicted_category_idx = max_element(prob_catsGivenStory.begin(), prob_catsGivenStory.end()) - prob_catsGivenStory.begin();
            string predicted_category = categories[predicted_category_idx];

            if ( predicted_category == labeled_category )
            {
                // correct
                correct_count = correct_count +1;   
            }
            else
            {
                // Tolerance some situations
                auto found = screenInfo_testing[ii].StoryTopicName.find("South-Ossetia");
                auto found1 = screenInfo_testing[ii].Screen_words.find("georgia");              
                if( labeled_category == "Human-interest" || 
                    labeled_category=="Celebrity" || 
                    labeled_category=="Entertainment" ||
                    predicted_category == "Human-interest" ||                   
                    predicted_category=="Entertainment"||
                    (predicted_category=="War"  && found < 50) ||       // war = south-Ossetia
                    (predicted_category == "International" && found < 50) ||    // international = south-Ossetia
                    (predicted_category=="War"      && found1 < 10000) ||
                    (labeled_category == "Justice"  && predicted_category == "Crime") || // justice = crime
                    (labeled_category == "Crime"    && predicted_category == "Justice") ||
                    (labeled_category == "Disaster"     && predicted_category == "Weather") ||  // disaster = weather
                    (labeled_category == "Weather"  && predicted_category == "Disaster") ||
                    (labeled_category == "Accident"     && predicted_category == "Crime") ||    // accident = crime
                    (labeled_category == "Crime"    && predicted_category == "Accident"))
                {
                    correct_count = correct_count +1;
                    predicted_category_idx = org_category_idx;
                }
                else
                {
                    fout_enhance << "Wrong: " << predicted_category << "\t [label: " << labeled_category << "]" << endl;
                    fout_enhance << setprecision(18) << "PredCat_Screen_Info: "<< screenInfo_testing[ii].StoryTimeStart<<"|"<<screenInfo_testing[ii].StoryTimeEnd<<"|"<<screenInfo_testing[ii].StoryTopicName<<endl;            
                    fout_enhance <<"PredCat_Screen_words: " << screenInfo_testing[ii].Screen_words << endl << endl;
                }
            }
            confusion_matrix[org_category_idx][predicted_category_idx] += 1;
        }

        double accuracy = double(correct_count)/(double)labels_testing.size();      
        crossValidation.push_back(accuracy);

        // Output confusion matrix and accuracy.
        fout_enhance << "Confusion Matrix:" << endl;
        for (int i=0; i<confusion_matrix.size(); i++)
        {
            for (int j=0; j<confusion_matrix.size(); j++)
            {
                fout_enhance << confusion_matrix[i][j]<< " ";
            }
            fout_enhance << endl;
        }
        fout_enhance << "Accuracy: \t" << accuracy << endl;
    }

    PrintCrossValidationReport(fout_eval, crossValidation);
    fout_eval.close();
}

// Output Cross validation report
void TextAnalysis::PrintCrossValidationReport(ostream& os, 
    const vector<double>& crossValidation)
{
    double accuracy_sum = 0;
    os << "--------------------------" << endl;
    os << "CROSS VALIDATION REPORT" << endl;
    os << "--------------------------" << endl;
    for ( int i=0; i < crossValidation.size(); i++)
    {
        accuracy_sum += crossValidation[i];
        os << "Accuracy (" << i << "):\t" << crossValidation[i] << endl;
    }

    os << "--------------------------" << endl;
    os << "AVG.: " << accuracy_sum/(double)crossValidation.size() << endl;
}

void TextAnalysis::TransitionMatrix_ScreenTopic(vector<ScreenInfo> &Screen_Info_Final){
        
    size_t found;
    int Category_Number=  27;
    vector<vector <int> > TranMat_ScTopic;
    vector<int> Building_Mat;
    for(int i=0; i < Category_Number; i++){ 
        Building_Mat.push_back(0);}
    for(int i=0; i < Category_Number; i++){     
        TranMat_ScTopic.push_back(Building_Mat);}

        const char* array[] = {"War","Sports", "Disaster" , "Accident","Activism", "Weather",
            "Social","Government","Science-technology","Religion","Politics", "International" ,
            "Lifestyle-leisure" , "Labor" , "Human-interest" , "Health" , "Environment" , 
            "Education" , "Business" ,  "Money" , "Crime", "Justice", "Art-culture", "Celebrity",
            "Entertainment", "Network" , "Commercial"};
        vector<string> categories(array, array + sizeof array / sizeof array[0]);
        int iIndix=0;
        for (int i=0; i<Screen_Info_Final.size(); i++){
            found = Screen_Info_Final[i].StoryTopicName.find("|");
            string Cat = Screen_Info_Final[i].StoryTopicName.substr( 0, found);
            for (int j=0; j<categories.size(); j++){
                if ( Cat.compare(categories[j]) == 0 ){
                    TranMat_ScTopic[iIndix][j] = TranMat_ScTopic[iIndix][j] + 1;
                    iIndix=j;
                }
            }
        }

    }


bool my_cmp(const WordCount& a, const WordCount& b)
{
    return a.Occurance > b.Occurance; // biggest comes first
}


// Input: FullDocs_in_NewFormat1.txt
// Output: Reference_Vocabulary1.txt
void TextAnalysis::Generate_Reference_Vocabulary()
{
//  ofstream FullDoc;
//  FullDoc.open ("FullDocs_in_NewFormat.txt");
//  for (int i=0; i<Story_InfoForTag.size(); i++){
//      FullDoc << "<story>" <<Story_InfoForTag[i].StoryTopicName << endl;
//      FullDoc << "<start>" <<Story_InfoForTag[i].StoryTimeStart << endl;
//      FullDoc << Story_InfoForTag[i].FullTopicName << endl;
//      FullDoc << "<end>" <<Story_InfoForTag[i].StoryTimeEnd << endl;}
//  FullDoc.close();
    ifstream ifs;
    ifs.open("FullDocs_in_NewFormat1.txt", ios::in);
    if (!ifs.is_open()) cout<<"File in FullDocs_in_NewFormat.txt NOT opened"<<endl;
    size_t found , found1 ;
    string str, str2;
    vector<StoryElements1> StoriesInfo;
    StoryElements1 entry;

    while (!ifs.eof() && ifs.good() )
    {

        char buffer[65536];
        ifs.getline(buffer, 65536);
        str = (buffer);
        found = str.find("|");
        if ( found == 18 ){
            str2 = str.substr (0  , found);
            entry.StoryTimeStart = str2;}
        if ( found == 14 ){
            str2 = str.substr (0  , found);
            entry.StoryTimeEnd = str2+".000";}


        str = str.substr (found+1  , str.size() );
        found = str.find("|");
        if ( found == 18 ){
            str2 = str.substr (0  , found);
            entry.StoryTimeEnd = str2;}


        str = str.substr (found+1  , str.size() );
        found = str.find("|");
        if ( found < 22 ){
            str2 = str.substr (0  , found);
            entry.StoryCat = str2;}

        str = str.substr (found+1  , str.size() );
        found = str.find("|");
        if ( found < 50 ){
            str2 = str.substr (0  , found);
            entry.StoryTopic = str2;}

        str = str.substr (found+1  , str.size() );
        entry.Words = str;
        StoriesInfo.push_back(entry);

    }

    cout<<"StoriesInfo.size    "<<StoriesInfo.size()<<endl;

    for ( int i =0; i<StoriesInfo.size(); i++)
    {
        found =  StoriesInfo[i].StoryTopic.find("South-Ossetia");
        found1 = StoriesInfo[i].Words.find("georgia");
////        if ( StoriesInfo[i].StoryCat != "Human-interest"|| StoriesInfo[i].StoryCat != "Entertainment"||
////            StoriesInfo[i].StoryCat != "Celebrity"){

        if ( StoriesInfo[i].StoryCat =="Crime")
        {  
            StoriesInfo[i].StoryCat = "Justice";
        }   
        if ( StoriesInfo[i].StoryCat =="Disaster")
        {  
            StoriesInfo[i].StoryCat = "Weather";
        }

    //      (predicted_category=="Crime" && labeled_category == "Accident")|| (
    //      predicted_category=="Accident" && labeled_category == "Crime")||
        if (found < 50 || found1 < 10000){
            StoriesInfo[i].StoryCat = "War";
        }
    }

    vector<string> labels_training;
    labels_training.clear();
    for( int i=0; i < StoriesInfo.size()-1; i++)
    {   
        labels_training.push_back(StoriesInfo[i].StoryCat);
    }

    const char* array[] = {"War","Sports", "Disaster" , "Accident","Activism", "Weather",
        "Social","Government","Science-technology","Religion","Politics", "International" ,
        "Lifestyle-leisure" , "Labor" , "Human-interest" , "Health" , "Environment" , 
        "Education" , "Business" ,  "Money" , "Crime", "Justice", "Art-culture", "Celebrity",
        "Entertainment", "Network" , "Commercial"};
    vector<string> CategoryList(array, array + sizeof array / sizeof array[0]);
        vector<int> ProbCat;
        ProbCat.clear();

    for(int i=0; i < CategoryList.size(); i++)
    {
        int Count = 0;
        for (int j=0; j < labels_training.size(); j++)
        {
            if (CategoryList[i].compare(labels_training[j]) == 0)
            {
                Count++;
            }
        }
        ProbCat.push_back(Count);
        //cout<<CategoryList[i]<<"      "<<Count<<endl;
    }

    //for (int j=0; j < labels_training.size(); j++){
    //cout<<"labels_training    "<<labels_training[j]<<""<<   <<endl;}
    //  if (NumberOfStory != labels_training.size()){
    //      cout<< " Error: Additional Category in Story list which NOT in The Main Category List"<< endl;
    //  }

    string AllWords_InEachCat;
    vector<string> AllWords_InAllCats;
    AllWords_InAllCats.clear();
    for(int i=0; i < CategoryList.size(); i++)
    {
        AllWords_InEachCat.clear();
        for (int j=0; j < StoriesInfo.size()-1; j++)
        {
            if (CategoryList[i].compare(StoriesInfo[j].StoryCat) == 0)
            {
                AllWords_InEachCat= StoriesInfo[j].Words +" "+  AllWords_InEachCat;
            }
        }
        AllWords_InAllCats.push_back(AllWords_InEachCat);
    }


    vector<string> VocabInEachCat, AllWords;
    ofstream inout;
    inout.open ("Reference_Vocabulary1.txt");

    for(int i=0; i < AllWords_InAllCats.size(); i++)
    { 
        VocabInEachCat.clear();
        AllWords.clear();
        istringstream iss(AllWords_InAllCats[i]);
        istringstream iss1(AllWords_InAllCats[i]);
        copy (istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(VocabInEachCat));
        copy (istream_iterator<string>(iss1), istream_iterator<string>(), back_inserter(AllWords));

        for(int k=0; k < VocabInEachCat.size(); k++)
        {
            for (int j=k+1; j < VocabInEachCat.size(); j++)
            {
                if (VocabInEachCat[k] != "" )
                {
                    if (VocabInEachCat[k].compare(VocabInEachCat[j]) == 0)
                    {
                        VocabInEachCat.erase (VocabInEachCat.begin()+j);
                        j--;
                    }
                }
            }
        }

        //cout<<"VocabInEachCat.size   "<<VocabInEachCat.size()<<"   AllWords.size   "<<AllWords.size()<<endl;
        inout<<"Category Name  ="<<CategoryList[i]<<endl;
        inout<<"Vocabulary Size  ="<<VocabInEachCat.size()<<"     "<<"All Words in "<<CategoryList[i]<<" Category = "<<AllWords.size()<<endl;

        WordCount entry;        
        vector<WordCount> Co_Occurance;
        for(int k=0; k < VocabInEachCat.size(); k++)
        {
            int Count = 0;
            for(int j=0; j < AllWords.size(); j++)
            {
                if (VocabInEachCat[k].compare(AllWords[j]) == 0)
                {
                    Count++;
                }
            }
            entry.Word = VocabInEachCat[k];
            entry.Occurance = Count;
            Co_Occurance.push_back(entry);          
        }

        sort(Co_Occurance.begin(), Co_Occurance.end(), my_cmp);
        //cout<<"Co_Occurance.size()     "<<Co_Occurance.size()<<endl;
        int Count = 0;
        for(int k=0; k < Co_Occurance.size(); k++)
        {
            inout<<Co_Occurance[k].Word<<" ("<<Co_Occurance[k].Occurance<<")"<<endl;
            Count = Count+Co_Occurance[k].Occurance;
        }

        inout<<endl<<endl;
    }

    inout.close();

}