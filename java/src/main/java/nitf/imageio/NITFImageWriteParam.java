package nitf.imageio;

import javax.imageio.ImageWriteParam;

import nitf.imageio.NITFUtilities.WriteCompression;
import nitf.imageio.wrapper.NITFProperties;

/**
 * Class holding Write parameters to customize the write operations
 * 
 * @author Daniele Romagnoli, GeoSolutions SaS
 */
public class NITFImageWriteParam extends ImageWriteParam {

    @Override
    public boolean canWriteCompressed() {
        return true;
    }

    @Override
    public boolean canWriteTiles() {
        return true;
    }
    
    //TODO Convert some of them as proper metadata entities (imageMetadata/streamMetadata)
    
    private WriteCompression writeCompression;
    
    private NITFProperties nitfProperties;
    
    public NITFProperties getNitfProperties() {
        return nitfProperties;
    }

    public void setNitfProperties(NITFProperties nitfProperties) {
        this.nitfProperties = nitfProperties;
    }

    public WriteCompression getWriteCompression() {
        return writeCompression;
    }

    public void setWriteCompression(WriteCompression writeCompression) {
        this.writeCompression = writeCompression;
    }

}