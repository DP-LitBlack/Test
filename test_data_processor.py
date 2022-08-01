import unittest
import os

TESTDATA_FILENAME = os.path.join(os.path.dirname(__file__), "log.txt")
RAWDATA_FILENAME = os.path.join(os.path.dirname(__file__), "sensor_data.txt")

class TestStringMethods(unittest.TestCase):
    
    def test_upper(self):
        self.testFile = open(TESTDATA_FILENAME)
        self.testData = self.testFile.read()
        self.testDataList = self.testData.split("\n")
        self.testDataList.pop()

        self.rawFile = open(RAWDATA_FILENAME)
        self.rawData = self.rawFile.read()
        self.rawDataList = self.rawData.split("\n")
        self.rawDataList.pop()

        j = 0

        for i in range(len(self.testDataList)): 
            if self.testDataList[i][0] == "p":
                print(j)
                self.assertEqual(int(self.testDataList[i][1:]), int(int(self.rawDataList[j]) / 2))
                j = j + 1
        
        self.testFile.close()
        self.rawFile.close()
        

        # print(self.testDataList)
        # self.assertEqual('foo'.upper(), 'FOO')

    # def test_isupper(self):
    #     self.assertTrue('FOO'.isupper())
    #     self.assertFalse('Foo'.isupper())

    # def test_split(self):
    #     s = 'hello world'
    #     self.assertEqual(s.split(), ['hello', 'world'])
    #     # check that s.split fails when the separator is not a string
    #     with self.assertRaises(TypeError):
    #         s.split(2)

if __name__ == '__main__':
    unittest.main()