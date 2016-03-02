#This script reads FinalError.txt
#ruby readErrorFinal.rb FinalError.txt
require 'csv'

#Open file
fname=ARGV[0]
infile=File.open(fname)
EOF=false

#Define CSV to put results there
CSV.open("ANCFIS_ELM_Result.csv","w") do |csv|
  csv<<["EpochNumber","TrainRMSE","CheckRMSE"]
end

experNo=0
#Read the first two lines *** and empty line
myline=infile.gets
myline=infile.gets
while !EOF do
  
  myline=infile.gets
  if myline.include?("EpochBest_Trn")
   temp=myline[/\d+/] 
  epoch=Integer(temp)
    myline=infile.gets
  end
if myline.include?("AveErrorBest_Trn")
    temp=myline[/\d+\.\d+/]
      trnRMSE=Float(temp)
  myline=infile.gets
end

  if myline.include?("FinalError_Chk")
    temp=myline[/\d+\.\d+/]
    chkRMSE=Float(temp)
    #Get the empty line
    myline=infile.gets
 end
 #Get *** line
  myline=infile.gets
 
 if experNo==0
   puts "EpochNumber,TrainRMSE,CheckRMSE"
 end 

   puts "#{epoch},#{trnRMSE},#{chkRMSE}" 
   
   CSV.open("ANCFIS_ELM_Result.csv","ab") do |csv|
      csv<<["#{epoch}","#{trnRMSE}","#{chkRMSE}"]

   end
  experNo+=1
  if myline.nil?
       break
     end
end

